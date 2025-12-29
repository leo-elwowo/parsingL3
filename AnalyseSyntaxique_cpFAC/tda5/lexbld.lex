%{
/*ex*/
#include "prs.tab.h"
%}
%option nounput
%option noinput
id [a-zA-Z_][a-zA-Z_0-9]*
divstar [ ]*[\/\*\%][ ]*
%%
{id} {fprintf(stderr,"identificateur détecté : <%s>\n",yytext); return ID;}
{divstar} {fprintf(stderr,"opération détectée : <%s>\n",yytext); return DIVSTAR;}
.|\n {fprintf(stderr,"non reconnu : <%c>\n",yytext[0]); return yytext[0];};
%%
