/**
 * servidor.js — Une el IDE (navegador) con el compilador EasyLang y con NASM.
 *
 * Requisitos: Node.js, nasm y ld (Linux o WSL en Windows).
 *             Se ensambla con nasm -f elf32 y se enlaza con ld -m elf_i386.
 *
 * Antes de iniciar, compilar el compilador dentro de CompiSintactico:
 *     bison -d Easylang.y
 *     flex Easylang.l
 *     gcc Easylang.tab.c lex.yy.c generador.c -o easylang
 *
 * Uso:        node servidor.js
 *
 * Rutas:
 *   POST http://localhost:3000/compilar  { fuente }        -> { ok, tac, asm, error }
 *   POST http://localhost:3000/ejecutar  { asm, entrada }  -> { ok, salida, error }
 *   POST http://localhost:3000/interpretar { tac, entrada } -> { ok, salida, error }
 *
 * El intérprete también se compila dentro de CompiSintactico:
 *     gcc interprete.c -o interprete
 *
 * CAMBIOS (resumen):
 *   1. Nueva ruta /compilar: recibe el código .el del editor, ejecuta el binario
 *      easylang (generado con Easylang.y y Easylang.l) y devuelve el código de tres
 *      direcciones y el código NASM. Antes el botón "Generar código" no tenía a quién llamar.
 *   2. Nueva función normalizarFuente(): limpia el texto del editor antes de compilar
 *      (ver la explicación en la función). Así no hay que modificar el lexer.
 *   3. El manejo de rutas ahora acepta /compilar y /ejecutar (antes solo /ejecutar).
 *   4. /ejecutar ensambla en 32 bits (elf32 + elf_i386), porque el generador produce
 *      código de 32 bits (int 0x80, esp, push dword). Con elf64 NASM lo rechazaba.
 *   5. Nueva ruta /interpretar: recibe el código de tres direcciones y lo ejecuta con
 *      el binario interprete (interprete.c), con los valores de INPUT en la entrada estándar.
 */
const http = require("http");
const fs = require("fs/promises");
const os = require("os");
const path = require("path");
const { execFile } = require("child_process");

const PUERTO = 3000;
const LIMITE_MS = 5000;   // tiempo máximo por paso (evita ciclos infinitos)

// CAMBIO 1: ubicación del compilador. servidor.js está en Frontend/ y el binario
// easylang se compila en la carpeta hermana CompiSintactico/.
const RUTA_COMPILADOR = path.join(__dirname, "..", "CompiSintactico", "easylang");
// CAMBIO 5: el intérprete (gcc interprete.c -o interprete) está en la misma carpeta
const RUTA_INTERPRETE = path.join(__dirname, "..", "CompiSintactico", "interprete");

function correr(comando, args, entrada = "") {
    return new Promise((resolve) => {
        const proceso = execFile(comando, args, { timeout: LIMITE_MS }, (error, stdout, stderr) => {
            resolve({ error, stdout, stderr });
        });
        proceso.stdin.on("error", () => {});   // el programa puede no leer toda la entrada
        proceso.stdin.end(entrada);
    });
}

/**
 * CAMBIO 2: normalizarFuente()
 * El lexer reconoce "BEGIN"\n, "END"\n, "MAIN"\n, "DO"\n y "do"\n, es decir, la palabra
 * reservada debe ir seguida inmediatamente de un salto de línea. Desde el editor web
 * pueden llegar tres casos que el lexer no acepta aunque el programa sea correcto:
 *   a) Saltos de línea de Windows (\r\n): el \r queda entre la palabra y el \n.
 *   b) Espacios o tabulaciones al final de la línea ("BEGIN  ").
 *   c) El último END sin Enter al final del archivo.
 * Se corrigen aquí, sin tocar Easylang.l. No se agregan ni quitan líneas,
 * por lo que los números de línea de los errores siguen siendo los del editor.
 */
function normalizarFuente(fuente) {
    return fuente
        .replace(/\r\n?/g, "\n")                     // a) \r\n o \r  ->  \n
        .split("\n")
        .map((linea) => linea.replace(/[ \t]+$/, "")) // b) quita espacios finales
        .join("\n")
        .replace(/\n*$/, "\n");                      // c) termina con un solo \n
}

/**
 * CAMBIO 1: compilar()
 * Guarda el código en una carpeta temporal y ejecuta:
 *     easylang programa.el programa.asm programa.tac
 * (es el uso que define main() en Easylang.y). Si hay error de sintaxis, easylang
 * termina con código 1 y escribe el mensaje de yyerror en stderr.
 */
async function compilar(fuente) {
    const carpeta = await fs.mkdtemp(path.join(os.tmpdir(), "easylang-"));
    const archivoEl = path.join(carpeta, "programa.el");
    const archivoAsm = path.join(carpeta, "programa.asm");
    const archivoTac = path.join(carpeta, "programa.tac");

    try {
        await fs.writeFile(archivoEl, normalizarFuente(fuente));

        const r = await correr(RUTA_COMPILADOR, [archivoEl, archivoAsm, archivoTac]);
        if (r.error) {
            // El binario no existe o no tiene permiso de ejecución
            if (r.error.code === "ENOENT" || r.error.code === "EACCES") {
                return {
                    ok: false,
                    error: "No se encontró el compilador en:\n" + RUTA_COMPILADOR +
                           "\n\nCompílalo dentro de CompiSintactico con:\n" +
                           "  bison -d Easylang.y\n  flex Easylang.l\n" +
                           "  gcc Easylang.tab.c lex.yy.c generador.c -o easylang"
                };
            }
            if (r.error.killed) {
                return { ok: false, error: `El compilador excedió el tiempo límite (${LIMITE_MS / 1000} s)` };
            }
            // Error léxico o sintáctico: es el mensaje de yyerror (línea y token)
            const detalle = (r.stderr || r.error.message).replaceAll(carpeta + path.sep, "");
            return { ok: false, error: "Error de compilación:\n" + detalle.trim() };
        }

        // Se leen los archivos generados (no el stdout) para obtener el texto exacto
        const tac = await fs.readFile(archivoTac, "utf8");
        const asm = await fs.readFile(archivoAsm, "utf8");
        return { ok: true, tac, asm };
    } finally {
        await fs.rm(carpeta, { recursive: true, force: true });
    }
}

/**
 * CAMBIO 5: interpretar()
 * Guarda el código de tres direcciones en programa.tac y ejecuta:
 *     interprete programa.tac
 * (es el uso que define main() en interprete.c). Los valores de INPUT llegan por la
 * entrada estándar, igual que en el ejecutable NASM. Si el intérprete encuentra un error
 * (división entre cero, instrucción no reconocida...) termina con código 1 y lo escribe en stderr.
 */
async function interpretar(tac, entrada) {
    const carpeta = await fs.mkdtemp(path.join(os.tmpdir(), "easylang-"));
    const archivoTac = path.join(carpeta, "programa.tac");

    try {
        await fs.writeFile(archivoTac, tac.endsWith("\n") ? tac : tac + "\n");

        const r = await correr(RUTA_INTERPRETE, [archivoTac], entrada);
        if (r.error) {
            if (r.error.code === "ENOENT" || r.error.code === "EACCES") {
                return {
                    ok: false,
                    error: "No se encontró el intérprete en:\n" + RUTA_INTERPRETE +
                           "\n\nCompílalo dentro de CompiSintactico con:\n  gcc interprete.c -o interprete"
                };
            }
            const motivo = r.error.killed
                ? `Tiempo límite excedido (${LIMITE_MS / 1000} s)`
                : "Error del intérprete:";
            return { ok: false, salida: r.stdout, error: motivo + (r.stderr ? "\n" + r.stderr.trim() : "") };
        }
        return { ok: true, salida: r.stdout };
    } finally {
        await fs.rm(carpeta, { recursive: true, force: true });
    }
}

async function ejecutar(asm, entrada) {
    const carpeta = await fs.mkdtemp(path.join(os.tmpdir(), "easylang-"));
    const archivoAsm = path.join(carpeta, "programa.asm");
    const objeto = path.join(carpeta, "programa.o");
    const ejecutable = path.join(carpeta, "programa");

    try {
        await fs.writeFile(archivoAsm, asm);

        // 1) Ensamblar. CAMBIO 4: el generador produce código de 32 bits (int 0x80, esp, push dword)
        let r = await correr("nasm", ["-f", "elf32", archivoAsm, "-o", objeto]);
        if (r.error) {
            const detalle = (r.stderr || r.error.message).replaceAll(archivoAsm, "programa.asm");
            return { ok: false, error: "Error al ensamblar (nasm):\n" + detalle };
        }

        // 2) Enlazar. CAMBIO 4: como ejecutable de 32 bits (elf_i386)
        r = await correr("ld", ["-m", "elf_i386", objeto, "-o", ejecutable]);
        if (r.error) return { ok: false, error: "Error al enlazar (ld):\n" + (r.stderr || r.error.message) };

        // 3) Ejecutar con los valores de INPUT en la entrada estándar
        r = await correr(ejecutable, [], entrada);
        if (r.error) {
            const motivo = r.error.killed
                ? `Tiempo límite excedido (${LIMITE_MS / 1000} s)`
                : `El programa terminó con código ${r.error.code}`;
            return { ok: false, salida: r.stdout, error: motivo + (r.stderr ? "\n" + r.stderr : "") };
        }
        return { ok: true, salida: r.stdout };
    } finally {
        await fs.rm(carpeta, { recursive: true, force: true });
    }
}

http.createServer(async (req, res) => {
    res.setHeader("Access-Control-Allow-Origin", "*");
    res.setHeader("Access-Control-Allow-Methods", "POST, OPTIONS");
    res.setHeader("Access-Control-Allow-Headers", "Content-Type");

    if (req.method === "OPTIONS") return res.writeHead(204).end();

    // CAMBIO 3: antes solo existía /ejecutar; ahora también /compilar y /interpretar (CAMBIO 5)
    const rutas = ["/compilar", "/ejecutar", "/interpretar"];
    if (req.method !== "POST" || !rutas.includes(req.url)) return res.writeHead(404).end();

    try {
        let cuerpo = "";
        for await (const parte of req) cuerpo += parte;
        const datos = JSON.parse(cuerpo);

        let resultado;
        if (req.url === "/compilar") {
            resultado = await compilar(String(datos.fuente || ""));
        } else if (req.url === "/interpretar") {
            resultado = await interpretar(String(datos.tac || ""), String(datos.entrada || ""));
        } else {
            resultado = await ejecutar(String(datos.asm || ""), String(datos.entrada || ""));
        }

        res.writeHead(200, { "Content-Type": "application/json" }).end(JSON.stringify(resultado));
    } catch (e) {
        res.writeHead(500, { "Content-Type": "application/json" })
           .end(JSON.stringify({ ok: false, error: "Error del servidor: " + e.message }));
    }
}).listen(PUERTO, "127.0.0.1", () => {
    console.log(`Servidor EasyLang en http://localhost:${PUERTO}`);
    console.log(`  POST /compilar  -> código de tres direcciones y NASM`);
    console.log(`  POST /ejecutar  -> ensambla, enlaza y ejecuta el NASM`);
    console.log(`  POST /interpretar -> ejecuta el código de tres direcciones`);
    console.log(`  Compilador: ${RUTA_COMPILADOR}`);
    console.log(`  Intérprete: ${RUTA_INTERPRETE}`);
});