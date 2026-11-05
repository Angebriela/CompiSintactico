const http = require("http");
const fs = require("fs/promises");
const os = require("os");
const path = require("path");
const { execFile } = require("child_process");

const PUERTO = 3000;
const LIMITE_MS = 5000;   // tiempo máximo por paso evita ciclos infinitos

const RUTA_COMPILADOR = path.join(__dirname, "..", "CompiSintactico", "easylang");

const RUTA_INTERPRETE = path.join(__dirname, "..", "CompiSintactico", "interprete");

function correr(comando, args, entrada = "") {
    return new Promise((resolve) => {
        const proceso = execFile(comando, args, { timeout: LIMITE_MS }, (error, stdout, stderr) => {
            resolve({ error, stdout, stderr });
        });
        proceso.stdin.on("error", () => {});
        proceso.stdin.end(entrada);
    });
}

//Normalizar fuente
function normalizarFuente(fuente) {
    return fuente
        .replace(/\r\n?/g, "\n")                    
        .split("\n")
        .map((linea) => linea.replace(/[ \t]+$/, "")) 
        .join("\n")
        .replace(/\n*$/, "\n");
}

//Ejecuta .asm y tac
async function compilar(fuente) {
    const carpeta = await fs.mkdtemp(path.join(os.tmpdir(), "easylang-"));
    const archivoEl = path.join(carpeta, "programa.el");
    const archivoAsm = path.join(carpeta, "programa.asm");
    const archivoTac = path.join(carpeta, "programa.tac");

    try {
        await fs.writeFile(archivoEl, normalizarFuente(fuente));

        const r = await correr(RUTA_COMPILADOR, [archivoEl, archivoAsm, archivoTac]);
        if (r.error) {
            // si el archivo binario no existe o no tiene permiso de ejecución
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

        const tac = await fs.readFile(archivoTac, "utf8");
        const asm = await fs.readFile(archivoAsm, "utf8");
        return { ok: true, tac, asm };
    } finally {
        await fs.rm(carpeta, { recursive: true, force: true });
    }
}

//guarda el codigo TDC en programa.tac y ejecuta
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
        let r = await correr("nasm", ["-f", "elf32", archivoAsm, "-o", objeto]);
        if (r.error) {
            const detalle = (r.stderr || r.error.message).replaceAll(archivoAsm, "programa.asm");
            return { ok: false, error: "Error al ensamblar (nasm):\n" + detalle };
        }

        r = await correr("ld", ["-m", "elf_i386", objeto, "-o", ejecutable]);
        if (r.error) return { ok: false, error: "Error al enlazar (ld):\n" + (r.stderr || r.error.message) };

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

//Creacion de servidor y metodos
http.createServer(async (req, res) => {
    res.setHeader("Access-Control-Allow-Origin", "*");
    res.setHeader("Access-Control-Allow-Methods", "POST, OPTIONS");
    res.setHeader("Access-Control-Allow-Headers", "Content-Type");

    if (req.method === "OPTIONS") return res.writeHead(204).end();

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