%{
/* tda1-ex1.lex */
%}

%option nounput
%option noinput

%%
the   printf("English ");
of    printf("English ");
and   printf("English ");
to    printf("English ");
a     printf("English ");
his   printf("English ");
in    printf("English ");
with  printf("English ");
I     printf("English ");
which printf("English ");
de  printf("français ");
à   printf("français ");
le  printf("français ");
la  printf("français ");
et  printf("français ");
il  printf("français ");
les printf("français ");
un  printf("français ");
en  printf("français ");
du  printf("français ");
[a-zA-ZâàçêéèëîïôûùüœÂÀÇÊÉÈËÎÏÔÛÙÜŒ]+ ;
. ;
%%
