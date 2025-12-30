%{
  /* Analyseur lexical pour les expressions arithmétiques */
  #include "expr_arith.h"
%}
%option nounput
%option noinput

%%
[[:blank:]]+             ; // horizontal whitespace, i.e. space and tab
[[:digit:]]+             {yylval.num = atoi(yytext);
                          return NUM;}
"+"                      return PLUS;
-                        return MINUS;
"*"                      return TIMES;
"/"                      return DIV;
"("                      return LPAREN;
")"                      return RPAREN;
.                        return yytext[0];
\n                       ;
%%

