%{
#include <stdio.h>
void yyerror(char*mensaje);
int yylex();

%}

%token ALLOCATE BEGIN1 END MAIN INPUT OUTPUT IF ELSE THEN AND OR DO WHILE FOR TO DO_CHIQUITO
%token ASIGNACION OPERADOR POTENCIA PUNTOYCOMA DOSPUNTOS PARENTESIS_IZQ PARENTESIS_DER
%token COMPARADOR1 COMPARADOR2 COMPARADOR3 COMPARADOR4 COMPARADOR5 COMENTARIO 
%token IDENTIFICADOR VALOR_INT SALTOLINEA INVALIDO
%%
inicio: MAIN BEGIN1 bloque_codigo otro_bloque_codigo  END {printf("Cadena válida\n");}
      | COMENTARIO MAIN BEGIN1 bloque_codigo otro_bloque_codigo END {printf("Cadena válida\n");}
      ;
bloque_codigo: identificador | input | output | instruccion
             ;
otro_bloque_codigo: bloque_codigo otro_bloque_codigo | vacio
                  ;
identificador : IDENTIFICADOR otro_identificador ALLOCATE PUNTOYCOMA
              ;
otro_identificador: DOSPUNTOS IDENTIFICADOR otro_identificador | vacio
                  ;   
input: INPUT IDENTIFICADOR PUNTOYCOMA
     ;
output: OUTPUT IDENTIFICADOR PUNTOYCOMA
      ;
potenciacion: VALOR_INT POTENCIA IDENTIFICADOR 
          ;  
condicion: IDENTIFICADOR comparador VALOR_INT | IDENTIFICADOR comparador IDENTIFICADOR
         ;
otra_condicion: operador_condicional condicion otra_condicion | vacio
             ;
operador_condicional: AND | OR
                 ;
comparador: COMPARADOR1 | COMPARADOR2 | COMPARADOR3 | COMPARADOR4 | COMPARADOR5
          ;
bloque_instrucciones: instruccion bloque_instrucciones  | instruccion 
                    ;
instruccion: IDENTIFICADOR ASIGNACION VALOR_INT PUNTOYCOMA | IDENTIFICADOR ASIGNACION IDENTIFICADOR PUNTOYCOMA
           | IDENTIFICADOR ASIGNACION potenciacion PUNTOYCOMA
           | IDENTIFICADOR ASIGNACION operacion otra_operacion PUNTOYCOMA
           | sentencia_if
           | repeticion_do
           | ciclo_for
           | COMENTARIO
           ;
operando: IDENTIFICADOR | VALOR_INT
        ;
operacion: operando OPERADOR operando
         ;
otra_operacion: OPERADOR operando otra_operacion | vacio
              ;

sentencia_if: IF PARENTESIS_IZQ condicion otra_condicion PARENTESIS_DER THEN BEGIN1 bloque_instrucciones END ELSE BEGIN1 bloque_instrucciones END
            ;
repeticion_do: DO bloque_instrucciones WHILE PARENTESIS_IZQ condicion otra_condicion PARENTESIS_DER 
            ;
ciclo_for: FOR for_do 
         ;
for_do: IDENTIFICADOR ASIGNACION for_to 
      ;

for_to: VALOR_INT TO VALOR_INT DO_CHIQUITO BEGIN1  bloque_instrucciones END
      | IDENTIFICADOR TO IDENTIFICADOR DO_CHIQUITO  BEGIN1  bloque_instrucciones END
      | VALOR_INT TO IDENTIFICADOR DO_CHIQUITO  BEGIN1  bloque_instrucciones END
      | IDENTIFICADOR TO VALOR_INT DO_CHIQUITO  BEGIN1  bloque_instrucciones END
      ;

vacio:
;
%%

void yyerror(char*mensaje){
    // extern por que esta en el archivo variables4.l o sea en el lexico
    extern int yylineno; 
    // extern por que esta en el archivo variables4.l o sea en el lexico
    extern char* yytext; 
    fprintf(stderr, "Error: %s en la linea %i cerca de %s\n", mensaje, yylineno, yytext);
}

int main(void){
   yyparse();
   return 0;
}
