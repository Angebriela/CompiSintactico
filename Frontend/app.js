/**
 * Muestra texto en uno de los visores (solo lectura), con números de línea.
 * idPanel: "codigoFuente", "codigoTresDir" o "codigoNasm"
 *
 * Cuando tengas el resultado del compilador, solo llama por ejemplo:
 *   mostrarCodigo("codigoTresDir", textoTresDirecciones);
 *   mostrarCodigo("codigoNasm", textoNasm);
 */
function mostrarCodigo(idPanel, texto) {
    const code = document.querySelector(`#${idPanel} code`);
    code.replaceChildren();

    const lineas = texto.replace(/\r\n?/g, "\n").split("\n");
    for (const linea of lineas) {
        const span = document.createElement("span");
        span.className = "linea";
        span.textContent = linea;   // textContent: no interpreta HTML
        code.appendChild(span);
    }
}

// ===== Carga del archivo fuente =====
// ===== Editor del archivo fuente (Abrir, Editar, Guardar) =====
const editor = document.getElementById("editorFuente");
const numerosLinea = document.getElementById("numerosLinea");
const entrada = document.getElementById("archivoEntrada");
const nombreArchivo = document.getElementById("nombreArchivo");

const tiposEl = [{ description: "Archivo EasyLang", accept: { "text/plain": [".el"] } }];
let nombreActual = "sin_titulo.el";
let manejadorArchivo = null;   // permite guardar sobre el mismo archivo (Chrome/Edge)
let hayCambios = false;

function actualizarNumeros() {
    const total = editor.value.split("\n").length;
    let numeros = "";
    for (let i = 1; i <= total; i++) numeros += i + "\n";
    numerosLinea.textContent = numeros;
    numerosLinea.scrollTop = editor.scrollTop;
}

function actualizarTitulo() {
    nombreArchivo.textContent = (hayCambios ? "● " : "") + nombreActual;
}

function cargarEnEditor(nombre, texto) {
    nombreActual = nombre;
    editor.value = texto.replace(/\r\n?/g, "\n");
    hayCambios = false;
    actualizarNumeros();
    actualizarTitulo();
}

function esArchivoEl(nombre) {
    if (nombre.toLowerCase().endsWith(".el")) return true;
    alert("Selecciona un archivo con extensión .el");
    return false;
}

// ---- Abrir ----
document.getElementById("botonAbrir").addEventListener("click", async () => {
    if (hayCambios && !confirm("Hay cambios sin guardar. ¿Abrir otro archivo?")) return;

    if (window.showOpenFilePicker) {
        try {
            const [handle] = await showOpenFilePicker({ types: tiposEl });
            const archivo = await handle.getFile();
            if (!esArchivoEl(archivo.name)) return;
            manejadorArchivo = handle;
            cargarEnEditor(archivo.name, await archivo.text());
        } catch (e) {
            if (e.name !== "AbortError") entrada.click();   // respaldo
        }
    } else {
        entrada.click();   // navegadores sin File System Access API
    }
});

entrada.addEventListener("change", async () => {
    const archivo = entrada.files[0];
    entrada.value = "";
    if (!archivo || !esArchivoEl(archivo.name)) return;
    manejadorArchivo = null;
    cargarEnEditor(archivo.name, await archivo.text());
});

// ---- Guardar ----
function descargarArchivo(contenido) {
    const nombre = nombreActual.toLowerCase().endsWith(".el") ? nombreActual : nombreActual + ".el";
    const url = URL.createObjectURL(new Blob([contenido], { type: "text/plain" }));
    const enlace = document.createElement("a");
    enlace.href = url;
    enlace.download = nombre;
    enlace.click();
    URL.revokeObjectURL(url);
}

// Siempre abre el cuadro "Guardar como" para elegir carpeta y nombre
async function guardarArchivo() {
    const contenido = editor.value;
    try {
        if (window.showSaveFilePicker) {
            const opciones = { suggestedName: nombreActual, types: tiposEl };
            if (manejadorArchivo) opciones.startIn = manejadorArchivo;   // abre en la carpeta del último archivo
            manejadorArchivo = await showSaveFilePicker(opciones);
            nombreActual = manejadorArchivo.name;

            const escritor = await manejadorArchivo.createWritable();
            await escritor.write(contenido);
            await escritor.close();
        } else {
            descargarArchivo(contenido);   // navegadores sin File System Access API
        }
    } catch (e) {
        if (e.name === "AbortError") return;   // el usuario canceló
        descargarArchivo(contenido);           // respaldo: descarga normal
    }
    hayCambios = false;
    actualizarTitulo();
}

document.getElementById("botonGuardar").addEventListener("click", guardarArchivo);

// ---- Limpiar ----
document.getElementById("botonLimpiar").addEventListener("click", () => {
    if (hayCambios && !confirm("Hay cambios sin guardar. ¿Limpiar de todos modos?")) return;
    manejadorArchivo = null;
    entrada.value = "";
    cargarEnEditor("sin_titulo.el", "");
    editor.focus();
});

// ---- Edición ----
editor.addEventListener("input", () => {
    hayCambios = true;
    actualizarNumeros();
    actualizarTitulo();
});

editor.addEventListener("scroll", () => {
    numerosLinea.scrollTop = editor.scrollTop;
});

editor.addEventListener("keydown", (e) => {
    if (e.key === "Tab") {                       // Tab inserta tabulación
        e.preventDefault();
        editor.setRangeText("\t", editor.selectionStart, editor.selectionEnd, "end");
        editor.dispatchEvent(new Event("input"));
    }
    if ((e.ctrlKey || e.metaKey) && e.key.toLowerCase() === "s") {   // Ctrl+S
        e.preventDefault();
        guardarArchivo();
    }
});

window.addEventListener("beforeunload", (e) => {
    if (hayCambios) e.preventDefault();
});

// Para el botón "Generar código": obtenerCodigoFuente() devuelve lo que hay en el editor
function obtenerCodigoFuente() {
    return editor.value;
}

// ===== CAMBIO: Generación de código (botón "Generar código") =====
// Antes el botón #botonGenerar no tenía ningún evento. Ahora envía el contenido del
// editor (el archivo .el abierto o lo escrito a mano) a servidor.js, que ejecuta el
// compilador hecho con Easylang.y y Easylang.l, y muestra lo que devuelve:
//   - código de tres direcciones  -> panel #codigoTresDir
//   - código NASM                 -> panel #codigoNasm
//   - errores léxicos/sintácticos -> panel #errores
const URL_COMPILAR = "http://localhost:3000/compilar";
const botonGenerar = document.getElementById("botonGenerar");

// CAMBIO: guarda el código fuente que produjo el NASM mostrado. "Ejecutar ASM" lo usa
// para saber cuántos INPUT pedir, aunque el editor se haya modificado después.
let fuenteCompilada = "";

botonGenerar.addEventListener("click", async () => {
    const fuente = obtenerCodigoFuente();
    if (!fuente.trim()) {
        alert("Abre un archivo .el o escribe código antes de generar.");
        return;
    }

    // Se limpian las salidas anteriores para no mezclar resultados de otro programa
    mostrarCodigo("codigoTresDir", "Compilando...");
    mostrarCodigo("codigoNasm", "Compilando...");
    mostrarCodigo("ejecucion", "");
    mostrarCodigo("codigoTDC", "");   // CAMBIO: también se limpia la salida del intérprete
    mostrarCodigo("errores", "");
    fuenteCompilada = "";
    botonGenerar.disabled = true;   // evita enviar dos veces mientras compila

    try {
        const respuesta = await fetch(URL_COMPILAR, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ fuente })
        });
        const datos = await respuesta.json();

        if (datos.ok) {
            mostrarCodigo("codigoTresDir", datos.tac.trimEnd());
            mostrarCodigo("codigoNasm", datos.asm.trimEnd());
            mostrarCodigo("errores", "Compilación exitosa: no se encontraron errores.");
            fuenteCompilada = fuente;
        } else {
            // Con errores el compilador no genera archivos: los paneles quedan vacíos
            // para que "Ejecutar ASM" no corra un código de una compilación anterior
            mostrarCodigo("codigoTresDir", "");
            mostrarCodigo("codigoNasm", "");
            mostrarCodigo("errores", datos.error);
        }
    } catch {
        mostrarCodigo("codigoTresDir", "");
        mostrarCodigo("codigoNasm", "");
        mostrarCodigo("errores",
            "No se pudo conectar con el servidor.\n" +
            "Verifica que servidor.js esté corriendo (node servidor.js) en " + URL_COMPILAR);
    } finally {
        botonGenerar.disabled = false;
    }
});

// ===== Ejecución del código NASM =====
// El navegador no puede ejecutar NASM: lo envía a servidor.js, que ensambla, enlaza y corre el programa.
const URL_EJECUTAR = "http://localhost:3000/ejecutar";

const modalEntradas = new bootstrap.Modal(document.getElementById("modalEntradas"));
const formEntradas = document.getElementById("formEntradas");
const camposEntradas = document.getElementById("camposEntradas");
const botonEjecutarAsm = document.getElementById("botonEjecutarAsm");

// Texto de un visor de solo lectura (sin los números de línea)
function obtenerTextoPanel(idPanel) {
    const lineas = document.querySelectorAll(`#${idPanel} .linea`);
    return Array.from(lineas, (linea) => linea.textContent).join("\n");
}

// Variables leídas con INPUT, en orden de aparición (sin contar comentarios *** ***)
function buscarLecturas(fuente) {
    const sinComentarios = fuente.replace(/\*\*\*[\s\S]*?\*\*\*/g, "");
    return Array.from(sinComentarios.matchAll(/\bINPUT\s+([A-Za-z][A-Za-z0-9]*)/g), (m) => m[1]);
}

// CAMBIO: la ventana de valores de INPUT ahora la usan dos botones ("Ejecutar ASM" y
// "Ejecutar TDC"). accionPendiente guarda qué hacer con los valores al presionar "Ejecutar".
let accionPendiente = null;

botonEjecutarAsm.addEventListener("click", () => {
    const asm = obtenerTextoPanel("codigoNasm");
    if (!asm.trim()) {
        alert("Primero genera el código NASM.");
        return;
    }
    // CAMBIO: antes el código para pedir las entradas estaba aquí; se movió a pedirEntradas()
    pedirEntradas((valores) => ejecutarAsm(asm, valores));
});

// CAMBIO: función nueva. Muestra un campo por cada INPUT del programa compilado y,
// al confirmar, llama a "accion" con los valores. Sin INPUT llama a "accion" de inmediato.
function pedirEntradas(accion) {
    // CAMBIO: antes usaba editor.value; ahora el código que realmente se compiló
    const lecturas = buscarLecturas(fuenteCompilada);
    if (lecturas.length === 0) {
        accion([]);
        return;
    }
    accionPendiente = accion;

    // Un campo por cada INPUT
    camposEntradas.replaceChildren();
    const veces = {};
    lecturas.forEach((variable, i) => {
        veces[variable] = (veces[variable] || 0) + 1;

        const grupo = document.createElement("div");
        grupo.className = "mb-3";

        const etiqueta = document.createElement("label");
        etiqueta.className = "form-label fw-semibold";
        etiqueta.htmlFor = `entrada${i}`;
        etiqueta.textContent = veces[variable] > 1 ? `${variable} (lectura ${veces[variable]})` : variable;

        const campo = document.createElement("input");
        campo.type = "number";
        campo.step = "1";
        campo.required = true;
        campo.className = "form-control";
        campo.id = `entrada${i}`;

        const aviso = document.createElement("div");
        aviso.className = "invalid-feedback";
        aviso.textContent = "Ingresa un número entero.";

        grupo.append(etiqueta, campo, aviso);
        camposEntradas.append(grupo);
    });

    formEntradas.classList.remove("was-validated");
    modalEntradas.show();
}

document.getElementById("modalEntradas").addEventListener("shown.bs.modal", () => {
    camposEntradas.querySelector("input")?.focus();
});

formEntradas.addEventListener("submit", (e) => {
    e.preventDefault();
    if (!formEntradas.checkValidity()) {
        formEntradas.classList.add("was-validated");
        return;
    }
    const valores = Array.from(camposEntradas.querySelectorAll("input"), (c) => c.value.trim());
    modalEntradas.hide();
    // CAMBIO: antes siempre llamaba a ejecutarAsm(); ahora ejecuta la acción del botón que abrió la ventana
    if (accionPendiente) accionPendiente(valores);
    accionPendiente = null;
});

async function ejecutarAsm(asm, valores) {
    mostrarCodigo("ejecucion", "Ensamblando y ejecutando...");
    botonEjecutarAsm.disabled = true;
    try {
        const respuesta = await fetch(URL_EJECUTAR, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ asm, entrada: valores.join("\n") + "\n" })
        });
        const datos = await respuesta.json();

        let texto = "";
        if (valores.length) texto += "Entradas: " + valores.join(", ") + "\n\n";
        texto += datos.salida || "(el programa no mostró salida)";
        if (!datos.ok) {
            texto += "\n\n" + datos.error;
            mostrarCodigo("errores", datos.error);
        }
        mostrarCodigo("ejecucion", texto);
    } catch {
        mostrarCodigo("ejecucion",
            "No se pudo conectar con el servidor de ejecución.\n" +
            "Verifica que servidor.js esté corriendo (node servidor.js) en " + URL_EJECUTAR);
    } finally {
        botonEjecutarAsm.disabled = false;
    }
}

// ===== CAMBIO: Ejecución del código de tres direcciones (intérprete) =====
// Sección nueva. El botón "Ejecutar TDC" envía el código de tres direcciones del panel
// #codigoTresDir a servidor.js, que lo ejecuta con interprete.c, y muestra la salida en
// el panel #codigoTDC ("Ejecución de TDC"). Usa la misma ventana de valores de INPUT.
const URL_INTERPRETAR = "http://localhost:3000/interpretar";
const botonEjecutarTdc = document.getElementById("botonEjecutarTdc");

botonEjecutarTdc.addEventListener("click", () => {
    const tac = obtenerTextoPanel("codigoTresDir");
    if (!tac.trim()) {
        alert("Primero genera el código de tres direcciones.");
        return;
    }
    pedirEntradas((valores) => ejecutarTdc(tac, valores));
});

async function ejecutarTdc(tac, valores) {
    mostrarCodigo("codigoTDC", "Interpretando...");
    botonEjecutarTdc.disabled = true;
    try {
        const respuesta = await fetch(URL_INTERPRETAR, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ tac, entrada: valores.join("\n") + "\n" })
        });
        const datos = await respuesta.json();

        let texto = "";
        if (valores.length) texto += "Entradas: " + valores.join(", ") + "\n\n";
        texto += datos.salida || "(el programa no mostró salida)";
        if (!datos.ok) {
            texto += "\n\n" + datos.error;
            mostrarCodigo("errores", datos.error);
        }
        mostrarCodigo("codigoTDC", texto);
    } catch {
        mostrarCodigo("codigoTDC",
            "No se pudo conectar con el servidor.\n" +
            "Verifica que servidor.js esté corriendo (node servidor.js) en " + URL_INTERPRETAR);
    } finally {
        botonEjecutarTdc.disabled = false;
    }
}

actualizarNumeros();