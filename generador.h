#ifndef GENERADOR_H
#define GENERADOR_H

/* Inicio y fin de la generacion */
int  iniciarGenerador(void);
int  escribirAsm(const char *nombre);

/* Tabla de nombres: lo que se reserva en section .bss */
void registrarVariable(const char *nombre);
void nuevaTem(char *temporal);
void nuevaEtq(char *etiqueta);

/* Cada gen* imprime el codigo de tres direcciones y escribe su equivalente NASM */
void genAsignacion(const char *destino, const char *valor);
void genOperacion(const char *destino, const char *izq, const char *op, const char *der);
void genInput(const char *variable);
void genOutput(const char *variable);
void genEtiqueta(const char *etiqueta);
void genGoto(const char *etiqueta);
void genIfz(const char *condicion, const char *etiqueta);
void genIfnz(const char *condicion, const char *etiqueta);

#endif