#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "generador.h"

/* ---------- Tabla de variables y temporales ---------- */
#define MAX_NOMBRES 2000

static char variables[MAX_NOMBRES][50];
static int  totalVariables = 0;
static char temporales[MAX_NOMBRES][50];
static int  totalTemporales = 0;

static FILE *codigo;           /* guarda section .text hasta conocer todos los temporales */
static int usaInput = 0;
static int usaOutput = 0;

int iniciarGenerador(void){
    codigo = tmpfile();
    if (!codigo) { perror("tmpfile"); return 1; }
    return 0;
}

static int esVariable(const char *nombre){
    for (int i = 0; i < totalVariables; i++)
        if (strcmp(variables[i], nombre) == 0) return 1;
    return 0;
}

void registrarVariable(const char *nombre){
    if (esVariable(nombre)) return;
    if (totalVariables == MAX_NOMBRES) { fprintf(stderr, "Error: demasiadas variables\n"); exit(1); }
    strcpy(variables[totalVariables++], nombre);
}

void nuevaTem(char *temporal){
    static int actual = 1;
    do {
        sprintf(temporal, "t%d", actual++);   /* no reutiliza una variable del programa llamada t1 */
    } while (esVariable(temporal));
    if (totalTemporales == MAX_NOMBRES) { fprintf(stderr, "Error: demasiados temporales\n"); exit(1); }
    strcpy(temporales[totalTemporales++], temporal);
}

void nuevaEtq(char *etiqueta){
    static int actual = 1;
    sprintf(etiqueta, "l%d", actual++);
}

/* Las variables llevan v_ porque en EasyLang un nombre no puede tener guion bajo.
   Asi una variable llamada add, ax, t1 o l1 nunca choca con NASM. */
static const char *ref(const char *nombre){
    static char texto[64];
    if (isdigit((unsigned char)nombre[0]) || nombre[0] == '-') strcpy(texto, nombre);
    else if (esVariable(nombre)) sprintf(texto, "[v_%s]", nombre);
    else sprintf(texto, "[%s]", nombre);
    return texto;
}

/* ---------- Generacion de codigo ---------- */
void genAsignacion(const char *destino, const char *valor){
    registrarVariable(destino);
    printf("     %s=%s;\n", destino, valor);
    fprintf(codigo, "    ; %s=%s\n", destino, valor);
    fprintf(codigo, "    mov eax, %s\n", ref(valor));
    fprintf(codigo, "    mov %s, eax\n", ref(destino));
}

static void genComparacion(const char *op){
    const char *instruccion = "sete";
    if      (strcmp(op, "<>") == 0) instruccion = "setne";
    else if (strcmp(op, "<")  == 0) instruccion = "setl";
    else if (strcmp(op, "<=") == 0) instruccion = "setle";
    else if (strcmp(op, ">")  == 0) instruccion = "setg";
    else if (strcmp(op, ">=") == 0) instruccion = "setge";
    fprintf(codigo, "    %s al\n", instruccion);       /* al = 1 si se cumple, 0 si no */
    fprintf(codigo, "    movzx eax, al\n");
}

void genOperacion(const char *destino, const char *izq, const char *op, const char *der){
    static int potencias = 0;
    const char *separador = isalpha((unsigned char)op[0]) ? " " : "";

    printf("     %s=%s%s%s%s%s;\n", destino, izq, separador, op, separador, der);
    fprintf(codigo, "    ; %s=%s%s%s%s%s\n", destino, izq, separador, op, separador, der);

    if (strcmp(op, "**") == 0) {            /* izq es el exponente y der la base */
        int n = ++potencias;
        fprintf(codigo, "    mov ecx, %s\n", ref(izq));
        fprintf(codigo, "    mov eax, 1\n");
        fprintf(codigo, "pot%d:\n", n);
        fprintf(codigo, "    cmp ecx, 0\n");
        fprintf(codigo, "    jle fin_pot%d\n", n);
        fprintf(codigo, "    imul eax, %s\n", ref(der));
        fprintf(codigo, "    dec ecx\n");
        fprintf(codigo, "    jmp pot%d\n", n);
        fprintf(codigo, "fin_pot%d:\n", n);
    } else {
        fprintf(codigo, "    mov eax, %s\n", ref(izq));
        if      (strcmp(op, "+")   == 0) fprintf(codigo, "    add eax, %s\n", ref(der));
        else if (strcmp(op, "-")   == 0) fprintf(codigo, "    sub eax, %s\n", ref(der));
        else if (strcmp(op, "*")   == 0) fprintf(codigo, "    imul eax, %s\n", ref(der));
        else if (strcmp(op, "AND") == 0) fprintf(codigo, "    and eax, %s\n", ref(der));
        else if (strcmp(op, "OR")  == 0) fprintf(codigo, "    or eax, %s\n", ref(der));
        else if (strcmp(op, "/")   == 0) {
            fprintf(codigo, "    mov ebx, %s\n", ref(der));   /* idiv no acepta constantes */
            fprintf(codigo, "    cdq\n");                     /* extiende eax a edx:eax */
            fprintf(codigo, "    idiv ebx\n");
        } else {
            fprintf(codigo, "    cmp eax, %s\n", ref(der));
            genComparacion(op);
        }
    }
    fprintf(codigo, "    mov %s, eax\n", ref(destino));
}

void genInput(const char *variable){
    registrarVariable(variable);
    usaInput = 1;
    printf("     call input;\n     pop %s;\n", variable);
    fprintf(codigo, "    ; call input / pop %s\n", variable);
    fprintf(codigo, "    call input\n");
    fprintf(codigo, "    pop dword %s\n", ref(variable));
}

void genOutput(const char *variable){
    registrarVariable(variable);
    usaOutput = 1;
    printf("     push %s;\n     call output;\n", variable);
    fprintf(codigo, "    ; push %s / call output\n", variable);
    fprintf(codigo, "    push dword %s\n", ref(variable));
    fprintf(codigo, "    call output\n");
}

void genEtiqueta(const char *etiqueta){
    printf("%s:\n", etiqueta);
    fprintf(codigo, "%s:\n", etiqueta);
}

void genGoto(const char *etiqueta){
    printf("     goto %s;\n", etiqueta);
    fprintf(codigo, "    jmp %s\n", etiqueta);
}

void genIfz(const char *condicion, const char *etiqueta){
    printf("     ifz %s goto %s\n", condicion, etiqueta);
    fprintf(codigo, "    mov eax, %s\n", ref(condicion));
    fprintf(codigo, "    cmp eax, 0\n");
    fprintf(codigo, "    je %s\n", etiqueta);
}

void genIfnz(const char *condicion, const char *etiqueta){
    printf("     ifnz %s goto %s\n", condicion, etiqueta);
    fprintf(codigo, "    mov eax, %s\n", ref(condicion));
    fprintf(codigo, "    cmp eax, 0\n");
    fprintf(codigo, "    jne %s\n", etiqueta);
}

/* ---------- Rutinas de entrada y salida ---------- */
/* input lee un entero por caracteres y lo deja en la pila */
static const char *RUTINA_INPUT =
    "\n; Lee un entero y lo deja en la pila\n"
    "input:\n"
    "    xor esi, esi        ; numero leido\n"
    "    xor edi, edi        ; 1 si es negativo\n"
    "    xor ebp, ebp        ; 1 si ya hubo digitos\n"
    ".leer:\n"
    "    mov eax, 3          ; syscall: sys_read\n"
    "    mov ebx, 0          ; entrada estandar\n"
    "    mov ecx, buffer\n"
    "    mov edx, 1          ; un caracter\n"
    "    int 0x80\n"
    "    cmp eax, 1\n"
    "    jl .fin             ; fin de la entrada\n"
    "    movzx eax, byte [buffer]\n"
    "    cmp eax, '-'\n"
    "    je .negativo\n"
    "    cmp eax, '0'\n"
    "    jl .separador\n"
    "    cmp eax, '9'\n"
    "    jg .separador\n"
    "    imul esi, esi, 10\n"
    "    sub eax, '0'\n"
    "    add esi, eax\n"
    "    mov ebp, 1\n"
    "    jmp .leer\n"
    ".negativo:\n"
    "    mov edi, 1\n"
    "    jmp .leer\n"
    ".separador:\n"
    "    cmp ebp, 0\n"
    "    je .leer            ; ignora espacios antes del numero\n"
    ".fin:\n"
    "    cmp edi, 0\n"
    "    je .guardar\n"
    "    neg esi\n"
    ".guardar:\n"
    "    pop eax             ; direccion de retorno\n"
    "    push esi            ; deja el numero en la pila\n"
    "    jmp eax\n";

/* output saca de la pila el numero y lo imprime */
static const char *RUTINA_OUTPUT =
    "\n; Saca un entero de la pila y lo imprime\n"
    "output:\n"
    "    mov eax, [esp+4]    ; numero a imprimir\n"
    "    mov esi, eax        ; guarda el signo\n"
    "    mov ebx, 10\n"
    "    mov ecx, buffer+15\n"
    "    mov byte [ecx], 10  ; salto de linea\n"
    "    cmp eax, 0\n"
    "    jge .digito\n"
    "    neg eax\n"
    ".digito:\n"
    "    xor edx, edx\n"
    "    div ebx             ; residuo en edx: ultimo digito\n"
    "    add dl, '0'\n"
    "    dec ecx\n"
    "    mov [ecx], dl\n"
    "    cmp eax, 0\n"
    "    jne .digito\n"
    "    cmp esi, 0\n"
    "    jge .escribir\n"
    "    dec ecx\n"
    "    mov byte [ecx], '-'\n"
    ".escribir:\n"
    "    mov edx, buffer+16\n"
    "    sub edx, ecx        ; cantidad de caracteres\n"
    "    mov eax, 4          ; syscall: sys_write\n"
    "    mov ebx, 1          ; salida estandar\n"
    "    int 0x80\n"
    "    ret 4               ; regresa y quita el numero de la pila\n";

/* ---------- Archivo .asm final ---------- */
int escribirAsm(const char *nombre){
    int c;
    FILE *salida = fopen(nombre, "w");
    if (!salida) { perror(nombre); return 1; }

    fprintf(salida, "section .bss\n");
    for (int i = 0; i < totalVariables; i++)
        fprintf(salida, "    v_%s resd 1\n", variables[i]);
    for (int i = 0; i < totalTemporales; i++)
        fprintf(salida, "    %s resd 1\n", temporales[i]);
    if (usaInput || usaOutput)
        fprintf(salida, "    buffer resb 16\n");

    fprintf(salida, "\nsection .text\n    global _start\n\n_start:\n");
    rewind(codigo);
    while ((c = fgetc(codigo)) != EOF) fputc(c, salida);

    fprintf(salida, "\n    ; finalizar el programa\n");
    fprintf(salida, "    mov eax, 1          ; syscall: sys_exit\n");
    fprintf(salida, "    xor ebx, ebx        ; codigo de salida 0\n");
    fprintf(salida, "    int 0x80\n");

    if (usaInput)  fputs(RUTINA_INPUT, salida);
    if (usaOutput) fputs(RUTINA_OUTPUT, salida);

    fclose(salida);
    return 0;
}