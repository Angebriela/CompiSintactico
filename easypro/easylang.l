%{
#include <stdio.h>
#include "easylang.tab.h"
%}

%option yylineno

%%
" "+"ALLOCATE"      {return ALLOCATE;}
"BEGIN"\n             {return BEGIN1;}
"END"\n               {return END;}
"MAIN"\n              {return MAIN;}
"INPUT"             {return INPUT;}
"OUTPUT"            {return OUTPUT;}
"IF"                {return IF;}
"ELSE"              {return ELSE;}
"THEN"              {return THEN;}
"AND"               {return AND;}
"OR"                {return OR;}
"DO"\n              {return DO;}
"WHILE"             {return WHILE;}
"FOR"               {return FOR;}
"to"                {return TO;}
"do"\n              {return DO_CHIQUITO;}
":="                {return ASIGNACION;}
[-+/*]              {return OPERADOR;}
"**"                {return POTENCIA;}
";"                 {return PUNTOYCOMA;}
":"                 {return DOSPUNTOS;}
"("                 {return PARENTESIS_IZQ;}
")"                 {return PARENTESIS_DER;}
[<>]                {return COMPARADOR1;}
"=="                {return COMPARADOR2;}
"<>"                {return COMPARADOR3;}
"<="                {return COMPARADOR4;}
">="                {return COMPARADOR5;}
"***"[^*\n]*"***"   {return COMENTARIO;}
[ \t\n]+            {}
[a-zA-Z][a-zA-Z0-9]* {return IDENTIFICADOR;}
[0-9]+              {return VALOR_INT;}
.                   {return INVALIDO;}    
%%

int yywrap(void){
    return 1;
}