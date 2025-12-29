%{
//exercice 1

%}

%option nounput
%option noinput
IDNT [a-zA-Z_][a-zA-Z_0-9]*
BLANCS [ \n\t]*
%x COMM
%%
\/\* {BEGIN COMM;} 
\/\/.*\n ;
{IDNT}/{BLANCS}\(   {printf("%s ", yytext);}
<*><<EOF>> {printf("\n"); return 0;}
<*>.|\n ;
<COMM>\*\/ {BEGIN INITIAL;}
%%
