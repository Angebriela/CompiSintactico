#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_LINEAS  20000
#define MAX_TEXTO   256
#define MAX_NOMBRES 5000
#define MAX_NOMBRE  50
#define MAX_PILA    1024

/* Datos del programa  */
typedef struct {
    char nombre[MAX_NOMBRE];
    int32_t valor;
} Variable;

typedef struct {
    char nombre[MAX_NOMBRE];
    int linea;
} Etiqueta;

static char lineas[MAX_LINEAS][MAX_TEXTO];
static int totalLineas = 0;

static Variable variables[MAX_NOMBRES];     /* variables y temporales */
static int totalVariables = 0;

static Etiqueta etiquetas[MAX_NOMBRES];
static int totalEtiquetas = 0;

static int32_t pila[MAX_PILA];
static int tope = 0;

static int lineaActual = 0;                 /* solo para los mensajes de error */

static void error(const char *mensaje, const char *detalle){
    fprintf(stderr, "Error en la linea %d: %s %s\n", lineaActual, mensaje, detalle);
    exit(1);
}

/*  Variables, etiquetas y pila  */
/* Busca una variable. Si no existe la crea en 0, igual que section .bss */
static Variable *buscarVariable(const char *nombre){
    for (int i = 0; i < totalVariables; i++)
        if (strcmp(variables[i].nombre, nombre) == 0) return &variables[i];

    if (totalVariables == MAX_NOMBRES) error("demasiadas variables:", nombre);
    strcpy(variables[totalVariables].nombre, nombre);
    variables[totalVariables].valor = 0;
    return &variables[totalVariables++];
}

static int buscarEtiqueta(const char *nombre){
    for (int i = 0; i < totalEtiquetas; i++)
        if (strcmp(etiquetas[i].nombre, nombre) == 0) return etiquetas[i].linea;
    error("no existe la etiqueta", nombre);
    return 0;
}

static void push(int32_t valor){
    if (tope == MAX_PILA) error("la pila esta llena", "");
    pila[tope++] = valor;
}

static int32_t pop(void){
    if (tope == 0) error("la pila esta vacia", "");
    return pila[--tope];
}

/*  Lectura de operandos y operadores */
static void leerNombre(const char **texto, char *nombre){
    int n = 0;
    while (isalnum((unsigned char)**texto)) {
        if (n == MAX_NOMBRE - 1) error("nombre demasiado largo:", *texto);
        nombre[n++] = *(*texto)++;
    }
    nombre[n] = '\0';
}

static void saltarEspacios(const char **texto){
    while (**texto == ' ') (*texto)++;
}

/* Un operando es un numero, con o sin signo, o el nombre de una variable */
static int32_t leerOperando(const char **texto){
    char nombre[MAX_NOMBRE];
    saltarEspacios(texto);

    if (**texto == '-' || isdigit((unsigned char)**texto)) {
        char *fin;
        long long numero = strtoll(*texto, &fin, 10);
        if (fin == *texto) error("operando no valido:", *texto);
        *texto = fin;
        return (int32_t)numero;
    }

    leerNombre(texto, nombre);
    if (nombre[0] == '\0') error("operando no valido:", *texto);
    return buscarVariable(nombre)->valor;
}

static const char *leerOperador(const char **texto){
    static const char *operadores[] = {
        "**", "<=", ">=", "==", "<>", "AND", "OR", "+", "-", "*", "/", "<", ">"
    };
    saltarEspacios(texto);
    for (int i = 0; i < 13; i++) {
        size_t largo = strlen(operadores[i]);
        if (strncmp(*texto, operadores[i], largo) == 0) {
            *texto += largo;
            return operadores[i];
        }
    }
    error("operador no reconocido:", *texto);
    return "";
}

/*  Operaciones  */
static int32_t multiplicar(int32_t a, int32_t b){
    return (int32_t)((uint32_t)a * (uint32_t)b);
}

static int32_t potencia(int32_t exponente, int32_t base){
    int32_t resultado = 1;
    for (int32_t i = exponente; i > 0; i--)
        resultado = multiplicar(resultado, base);
    return resultado;
}

static int32_t operar(int32_t a, const char *op, int32_t b){
    if (strcmp(op, "+")   == 0) return (int32_t)((uint32_t)a + (uint32_t)b);
    if (strcmp(op, "-")   == 0) return (int32_t)((uint32_t)a - (uint32_t)b);
    if (strcmp(op, "*")   == 0) return multiplicar(a, b);
    if (strcmp(op, "**")  == 0) return potencia(a, b);
    if (strcmp(op, "AND") == 0) return a & b;
    if (strcmp(op, "OR")  == 0) return a | b;
    if (strcmp(op, "<")   == 0) return a < b;
    if (strcmp(op, ">")   == 0) return a > b;
    if (strcmp(op, "<=")  == 0) return a <= b;
    if (strcmp(op, ">=")  == 0) return a >= b;
    if (strcmp(op, "==")  == 0) return a == b;
    if (strcmp(op, "<>")  == 0) return a != b;

    if (b == 0) error("division entre cero", "");
    if (a == INT32_MIN && b == -1) error("resultado de la division fuera de rango", "");
    return a / b;
}

/* Lee un entero como lo hace la rutina input del codigo NASM */
static int32_t leerEntero(void){
    uint32_t numero = 0;
    int negativo = 0, hayDigitos = 0, c;

    while ((c = getchar()) != EOF) {
        if (c == '-') {
            negativo = 1;
        } else if (isdigit(c)) {
            numero = numero * 10 + (uint32_t)(c - '0');
            hayDigitos = 1;
        } else if (hayDigitos) {
            break;                      /* el separador termina el numero */
        }
    }
    return (int32_t)(negativo ? 0u - numero : numero);
}

/* Carga del archivo  */
static void limpiar(char *linea){
    size_t inicio = strspn(linea, " \t");
    size_t largo;

    memmove(linea, linea + inicio, strlen(linea + inicio) + 1);
    largo = strlen(linea);
    while (largo > 0 && strchr(" \t\r\n;", linea[largo - 1])) linea[--largo] = '\0';
}

static void cargarPrograma(const char *nombreArchivo){
    char texto[MAX_TEXTO];
    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo) { perror(nombreArchivo); exit(1); }

    while (fgets(texto, sizeof(texto), archivo)) {
        size_t largo;
        lineaActual = totalLineas + 1;
        if (totalLineas == MAX_LINEAS) error("el programa tiene demasiadas lineas", "");

        limpiar(texto);
        strcpy(lineas[totalLineas], texto);
        largo = strlen(texto);

        /* Una etiqueta guarda la linea en la que esta */
        if (largo > 0 && texto[largo - 1] == ':') {
            if (totalEtiquetas == MAX_NOMBRES) error("demasiadas etiquetas:", texto);
            if (largo > MAX_NOMBRE) error("nombre demasiado largo:", texto);
            texto[largo - 1] = '\0';
            strcpy(etiquetas[totalEtiquetas].nombre, texto);
            etiquetas[totalEtiquetas].linea = totalLineas;
            totalEtiquetas++;
        }
        totalLineas++;
    }
    fclose(archivo);
}

/* Ejecucion */
static void asignar(const char *destino, const char *expresion){
    int32_t izquierda = leerOperando(&expresion);
    int32_t resultado = izquierda;

    saltarEspacios(&expresion);
    if (*expresion != '\0') {
        const char *op = leerOperador(&expresion);
        int32_t derecha = leerOperando(&expresion);
        resultado = operar(izquierda, op, derecha);
    }
    buscarVariable(destino)->valor = resultado;
}

static void ejecutar(void){
    int pc = 0;

    while (pc < totalLineas) {
        const char *linea = lineas[pc];
        const char *resto = linea;
        char nombre[MAX_NOMBRE], etiqueta[MAX_NOMBRE];
        size_t largo = strlen(linea);

        lineaActual = pc + 1;
        pc++;

        if (largo == 0 || linea[largo - 1] == ':') continue;   /* vacia o etiqueta */

        leerNombre(&resto, nombre);

        if (*resto == '=') {                                   /* a=1 o t1=a+b */
            asignar(nombre, resto + 1);
        } else if (strcmp(linea, "call input") == 0) {
            push(leerEntero());
        } else if (strcmp(linea, "call output") == 0) {
            printf("%d\n", pop());
            fflush(stdout);
        } else if (strcmp(nombre, "push") == 0) {
            push(leerOperando(&resto));
        } else if (sscanf(linea, "pop %49s", nombre) == 1) {
            buscarVariable(nombre)->valor = pop();
        } else if (sscanf(linea, "goto %49s", etiqueta) == 1) {
            pc = buscarEtiqueta(etiqueta);
        } else if (sscanf(linea, "ifz %49s goto %49s", nombre, etiqueta) == 2) {
            if (buscarVariable(nombre)->valor == 0) pc = buscarEtiqueta(etiqueta);
        } else if (sscanf(linea, "ifnz %49s goto %49s", nombre, etiqueta) == 2) {
            if (buscarVariable(nombre)->valor != 0) pc = buscarEtiqueta(etiqueta);
        } else {
            error("instruccion no reconocida:", linea);
        }
    }
}

int main(int argc, char **argv){
    cargarPrograma((argc > 1) ? argv[1] : "salida.tac");
    ejecutar();
    return 0;
}