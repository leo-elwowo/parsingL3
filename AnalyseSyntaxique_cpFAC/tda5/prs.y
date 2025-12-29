%{
/*analyseur syntaxique*/
#include <stdio.h>
int yylex(void);
void yyerror(char * msg);
%}
%token ID
%token DIVSTAR
%%
T   : T DIVSTAR ID
    | ID
    ;
%%
void yyerror(char * msg){
    printf("\nexpression invalide\n");
}
int main(void){
    int i = yyparse();
    if (i == 0){
        printf("\nexpression valide\n");
        return 0;
    }
    return 1;
}