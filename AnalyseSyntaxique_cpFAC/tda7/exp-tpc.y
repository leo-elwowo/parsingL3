%{
/* exp-tpc.y */
/* Syntaxe des expressions en TPC */
#include <stdio.h>
int yylex();
void yyerror(char *);
%}
%union {
    char byte;
    int num;
    char ident[64];
    char comp[3];
}

%token <byte> CHARACTER ADDSUB DIVSTAR
%token <num> NUM
%token <ident> IDENT
%token <comp> ORDER EQ
%token OR
%token AND

%%
Exp :  Exp OR TB 
    |  TB 
    ;
TB  :  TB AND FB 
    |  FB 
    ;
FB  :  FB EQ M
    |  M
    ;
M   :  M ORDER E 
    |  E 
    ;
E   :  E ADDSUB T 
    |  T 
    ;    
T   :  T DIVSTAR F 
    |  F 
    ;
F   :  ADDSUB F        
    |  '!' F 
    |  '(' Exp ')' 
    |  NUM 
    |  CHARACTER
    |  LValue  
    |  IDENT '(' Arguments ')' 
    ;
LValue:
       IDENT 
    ;
Arguments:
       ListExp 
    | ;
ListExp:
       ListExp ',' Exp 
    |  Exp 
    ;
%%
void yyerror(char * msg){
    fprintf(stderr ,"\texpression invalide\n");
}
int main(int argc, char **argv) {
  return yyparse();
}
