%{
//exercice 1
#include "exp-tpc.tab.h"
#include <string.h>
%}

%option nounput
%option noinput
IDENT [a-zA-Z_][a-zA-Z_0-9]*
BLANCS [ \n\t]*
%x COMM
%%
\/\* {BEGIN COMM;} 
\/\/.*\n ;
{BLANCS} ;
{IDENT} {
        strcpy(yylval.ident, yytext) ;
        fprintf(stderr, "detecte ident %s\n", yytext);
        return IDENT; }
[+-] {
        yylval.byte = yytext[0];
        fprintf(stderr, "detecte addsub %s\n", yytext);
        return ADDSUB; }
[\/\*\%] {
        yylval.byte = yytext[0];
        fprintf(stderr, "detecte divstar %s\n", yytext);
        return DIVSTAR; }
[0-9]+ {
        yylval.num =atoi(yytext);
        fprintf(stderr, "detecte num %s\n", yytext);
        return NUM; }
\&\& {
        fprintf(stderr, "detecte et %s\n", yytext);
        return AND;}
\|\| {
        fprintf(stderr, "detecte OU %s\n", yytext);
        return OR;}
\=\=|\!\= {
        strcpy(yylval.comp, yytext) ;
        fprintf(stderr, "detecte eq %s\n", yytext);
        return EQ;}
[<>]|\<\=|\>\= {
        strcpy(yylval.comp, yytext) ;
        fprintf(stderr, "detecte order %s\n", yytext);
        return ORDER;}
[!;,\(\)\{\}] {
        fprintf(stderr, "detecte char %s\n", yytext);
        return yytext[0];
}
<*><<EOF>> {printf("\n"); return 0;}
<COMM>.|\n ;
<COMM>\*\/ {BEGIN INITIAL;}
%%
