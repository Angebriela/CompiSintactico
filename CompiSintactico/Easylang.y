%{
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "generador.h"

void yyerror(char *mensaje);
int yylex();
%}

%union{
    char cadena[50];
}

%token ALLOCATE BEGIN1 END MAIN INPUT OUTPUT IF ELSE THEN AND OR DO WHILE FOR TO DO_CHIQUITO
%token ASIGNACION SUMA RESTA MUL DIV POTENCIA PUNTOYCOMA DOSPUNTOS PARENTESIS_IZQ PARENTESIS_DER
%token COMENTARIO INVALIDO
%token <cadena> IDENTIFICADOR VALOR_INT COMPARADOR
%type <cadena> operando factor expresion termino condicion condiciones

%%
inicio: MAIN { printf("main:\n"); } BEGIN1 bloque_codigo otro_bloque_codigo END
      | COMENTARIO MAIN { printf("main:\n"); } BEGIN1 bloque_codigo otro_bloque_codigo END
      ;
bloque_codigo: identificador | instruccion
      ;
otro_bloque_codigo: bloque_codigo otro_bloque_codigo | vacio
      ;
identificador: IDENTIFICADOR { registrarVariable($1); } otro_identificador ALLOCATE PUNTOYCOMA
      ;
otro_identificador: DOSPUNTOS IDENTIFICADOR { registrarVariable($2); } otro_identificador
      | vacio
      ;
input: INPUT IDENTIFICADOR PUNTOYCOMA   { genInput($2); }
      ;
output: OUTPUT IDENTIFICADOR PUNTOYCOMA { genOutput($2); }
      ;

/*  Asignaciones y operaciones */
instruccion: IDENTIFICADOR ASIGNACION expresion PUNTOYCOMA    { genAsignacion($1,$3); }
      | input
      | output
      | sentencia_if
      | repeticion_do
      | ciclo_for
      | COMENTARIO
      ;
expresion: expresion SUMA termino   { nuevaTem($$); genOperacion($$,$1,"+",$3); }
      | expresion RESTA termino     { nuevaTem($$); genOperacion($$,$1,"-",$3); }
      | termino                     { strcpy($$,$1); }
      ;
termino: termino MUL factor         { nuevaTem($$); genOperacion($$,$1,"*",$3); }
      | termino DIV factor          { nuevaTem($$); genOperacion($$,$1,"/",$3); }
      | factor                      { strcpy($$,$1); }
      ;
factor: operando POTENCIA operando  { nuevaTem($$); genOperacion($$,$1,"**",$3); }
      | operando                    { strcpy($$,$1); }
      ;
operando: IDENTIFICADOR             { registrarVariable($1); strcpy($$,$1); }
      | VALOR_INT                   { strcpy($$,$1); }
      | RESTA VALOR_INT             { strcpy($$,"-"); strcat($$,$2); }
      | PARENTESIS_IZQ expresion PARENTESIS_DER { strcpy($$,$2); }
      ;

/* Condiciones */
condiciones: condicion              { strcpy($$,$1); }
      | condiciones AND condicion   { nuevaTem($$); genOperacion($$,$1,"AND",$3); }
      | condiciones OR condicion    { nuevaTem($$); genOperacion($$,$1,"OR",$3); }
      ;
condicion: IDENTIFICADOR COMPARADOR operando { registrarVariable($1); nuevaTem($$); genOperacion($$,$1,$2,$3); }
      ;

bloque_instrucciones: instruccion bloque_instrucciones | instruccion
      ;

/* Control de flujo  */
sentencia_if: IF PARENTESIS_IZQ condiciones PARENTESIS_DER THEN BEGIN1
        { nuevaEtq($<cadena>$); genIfz($3,$<cadena>$); }
        bloque_instrucciones END    
        { nuevaEtq($<cadena>$); genGoto($<cadena>$); genEtiqueta($<cadena>7); }
        ELSE BEGIN1 bloque_instrucciones END
        { genEtiqueta($<cadena>10); }
      ;

repeticion_do: DO
        { nuevaEtq($<cadena>$); genEtiqueta($<cadena>$); }
        bloque_instrucciones WHILE PARENTESIS_IZQ condiciones PARENTESIS_DER
        { genIfnz($6,$<cadena>2); }
      ;

ciclo_for: FOR IDENTIFICADOR ASIGNACION operando TO operando DO_CHIQUITO BEGIN1
        { genAsignacion($2,$4); nuevaEtq($<cadena>$); genEtiqueta($<cadena>$); }
        { char t[50]; nuevaTem(t); genOperacion(t,$2,"<=",$6);
          nuevaEtq($<cadena>$); genIfz(t,$<cadena>$); }
        bloque_instrucciones END
        { char t[50]; nuevaTem(t); genOperacion(t,$2,"+","1"); genAsignacion($2,t);
          genGoto($<cadena>9); genEtiqueta($<cadena>10); }
      ;

vacio:
      ;
%%

void yyerror(char *mensaje){
    extern int yylineno;
    extern char *yytext;
    fprintf(stderr, "Error: %s en la linea %i cerca de %s\n", mensaje, yylineno, yytext);
}

/*escribe salida.asm y salida.tac */
int main(int argc, char **argv){
    extern FILE *yyin;
    const char *nombreSalida = (argc > 2) ? argv[2] : "salida.asm";
    const char *nombreTac = (argc > 3) ? argv[3] : "salida.tac";
    FILE *tac;
    int pantalla, resultado, c;

    if (argc > 1 && !(yyin = fopen(argv[1], "r"))) { perror(argv[1]); return 1; }

    if (iniciarGenerador() != 0) return 1;

    /* Mientras se analiza, los printf del codigo de tres direcciones van al archivo */
    pantalla = dup(STDOUT_FILENO);
    if (!freopen(nombreTac, "w", stdout)) { perror(nombreTac); return 1; }
    resultado = yyparse();
    fflush(stdout);
    dup2(pantalla, STDOUT_FILENO);     

    if (resultado != 0) {              
        remove(nombreTac);
        return 1;
    }

    tac = fopen(nombreTac, "r");
    if (!tac) { perror(nombreTac); return 1; }
    while ((c = fgetc(tac)) != EOF) putchar(c);
    fclose(tac);

    return escribirAsm(nombreSalida);
}