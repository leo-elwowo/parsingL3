%{
/* tda1-ex1.lex */
int compteanglais = 0;
int comptefrancais = 0;
int affiche_langue(int ang,int fra);
%}

%option nounput
%option noinput

%%
the   compteanglais++;
of    compteanglais++;
and   compteanglais++;
to    compteanglais++;
a     compteanglais++;
his   compteanglais++;
in    compteanglais++;
with  compteanglais++;
I     compteanglais++;
which compteanglais++;
de  comptefrancais++;
à   comptefrancais++;
le  comptefrancais++;
la  comptefrancais++;
et  comptefrancais++;
il  comptefrancais++;
les comptefrancais++;
un  comptefrancais++;
en  comptefrancais++;
du  comptefrancais++;
[a-zA-ZâàçêéèëîïôûùüœÂÀÇÊÉÈËÎÏÔÛÙÜŒ]+ { /*pas d'action*/ } ;
<<EOF>> { affiche_langue(compteanglais,comptefrancais) ; return 0 ; }
\n ; 
. { /*pas d'action*/ } ;

%%
int affiche_langue(int ang,int fra){
    /*
    prend deux variables, une qui a compté le nombre de mots francais, et
    une qui a compté le nombre de mots
    */
    if (ang==fra){
        printf("aussi anglais que francais\n");
    }
    else if (ang>fra){
        printf("anglais\n");
    }
    else{
        printf("francais\n");
    }
    return 0;
}
