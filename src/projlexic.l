%{
//exercice 1
#include "tpc-2025-2026.tab.h"
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

\/\/.* ;

if            {return IF;}
else          {return ELSE;}
while         {return WHILE;}
return        {return RETURN;}
struct        {return STRUCT;} 
int           {strcpy(yylval.ident, yytext); return TYPE;}  
char          {strcpy(yylval.ident, yytext); return TYPE;}
void          {return VOID;}

{IDENT} {
        strcpy(yylval.ident, yytext) ;
        return IDENT; }

[+-] {
        yylval.byte = yytext[0];
        return ADDSUB; }
[\/\*\%] {
        yylval.byte = yytext[0];
        return DIVSTAR; }

\'\\n\'         {yylval.character = '\n'; return CHARACTER;}
\'\\t\'         {yylval.character = '\t'; return CHARACTER;}
\'.\' {
    yylval.character = yytext[1];
    return CHARACTER;
}

[0-9]+ {
        yylval.num =atoi(yytext);
        return NUM; }
\&\& {
        return AND;}
\|\| {
        return OR;}
\=\=|\!\= {
        strcpy(yylval.comp, yytext) ;
        return EQ;}
[<>]|\<\=|\>\= {
        strcpy(yylval.comp, yytext) ;
        return ORDER;}
[!;,\(\)\{\}\[\]\.=] {
        return yytext[0];
}

{BLANCS} ;
\n {lineno++;}
<*><<EOF>> {printf("\n"); return 0;}

%%
