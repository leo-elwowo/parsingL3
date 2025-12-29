%{
/*ex5*/
char decalage(int c);
%}
%option nounput
%option noinput
%%
[a-zA-Z] { printf("%c",decalage(yytext[0])) ; }
%%
char decalage(int c){
    if ((c >= 97 && c <=121) || (c>= 65 && c <= 89)){
        return (char)(c+1);
    }
    else if (c == 90 || c == 122){
        return (char)(c-25);
    }
    else
        return (char)c;
}