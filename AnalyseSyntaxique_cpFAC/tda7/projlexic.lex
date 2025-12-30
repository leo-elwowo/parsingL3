%{
//exercice 1
#include "exp-tpc.tab.h"
#include <string.h>

int lineno = 1;
%}

%option nounput
%option noinput

IDENT [a-zA-Z_][a-zA-Z_0-9]*
BLANCS [ \t]+

%x COMM

%%

\/\* {BEGIN COMM;} 
<COMM>. ;
<COMM>\n {lineno++;}
<COMM>\*\/ {BEGIN INITIAL;}

\/\/.*\n ;

if            {return IF;}
else          {return ELSE;}
while         {return WHILE;}
return        {return RETURN;}
struct        {return STRUCT;} 
int           {return TYPE;}  
char          {return TYPE;} 
void          {return VOID;}

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

{BLANCS} ;
\n {lineno++;}
<*><<EOF>> {printf("\n"); return 0;}

%%
