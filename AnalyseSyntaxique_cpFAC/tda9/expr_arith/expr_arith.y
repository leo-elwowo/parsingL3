%{
  /* expr_arith.y */
  /* Syntaxe des expressions arithmétiques */
#include <stdio.h>
int yylex();
void yyerror(char *);
%}
%union {
    int num;
}
%token <num> NUM
%token PLUS MINUS TIMES DIV LPAREN RPAREN

%%
Expr:
Expr PLUS Expr
|  Expr MINUS Expr
|  Expr TIMES Expr
|  Expr DIV Expr
|  LPAREN Expr RPAREN
|  NUM
       ;
%%

void yyerror(char * msg){
  fprintf(stderr, "%s\n", msg);
}

int main(int argc, char** argv) {
  return yyparse();
}
