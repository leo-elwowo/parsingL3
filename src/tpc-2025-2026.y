%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int yylex();
void yyerror(const char *s);
extern int lineno;

Node *root = NULL;

%}

%union {
    int num;
    char ident[64];
    char byte;
    char character;
    char comp[4];
    Node *node;
}

%token <num> NUM
%token <ident> IDENT
%token <character> CHARACTER
%token <byte> ADDSUB DIVSTAR
%token <comp> EQ ORDER
%token IF ELSE WHILE RETURN STRUCT TYPE VOID AND OR

%type <node> Prog DeclVars DeclFoncts DeclFonct EnTeteFonct Parametres ListTypVar
%type <node> Corps SuiteInstr Instr Exp TB FB M E T F Arguments ListExp
%type <node> DeclStructs DeclStruct TypeName LValue

%%
Prog:  DeclStructs DeclVars DeclFoncts
    ;
DeclStructs:
        DeclStructs DeclStruct 
        { 
           $$ = $1; 
           if ($$ == NULL) $$ = makeNode(LIST); /* Création liste si vide */
           addChild($$, $2); 
        }
    |  { $$ = NULL; }
    ;

DeclStruct:
       STRUCT IDENT '{' DeclVars '}' ';'
       {
           $$ = makeNode(STRUCT_DECL);
           /* On stocke le nom de la struct dans le noeud STRUCT_DECL ou un fils */
           Node *nId = makeNode(IDENT); strcpy(nId->ident, $2);
           addChild($$, nId);
           addChild($$, $4); /* Les champs */
       }
    ;
DeclVars:
       DeclVars TYPE Declarateurs ';'
    |
    ;
Declarateurs:
       Declarateurs ',' IDENT
    |  IDENT
    ;
DeclFoncts:
       DeclFoncts DeclFonct
    |  DeclFonct
    ;
DeclFonct:
       EnTeteFonct Corps
    ;
EnTeteFonct:
       TYPE IDENT '(' Parametres ')'
    |  VOID IDENT '(' Parametres ')'
    ;
Parametres:
       VOID
    |  ListTypVar
    ;
ListTypVar:
       ListTypVar ',' TYPE IDENT
    |  TYPE IDENT
    ;
Corps: '{' DeclVars SuiteInstr '}'
    ;
SuiteInstr:
       SuiteInstr Instr
    |
    ;
Instr:
       IDENT '=' Exp ';'
    |  IF '(' Exp ')' Instr
    |  IF '(' Exp ')' Instr ELSE Instr
    |  WHILE '(' Exp ')' Instr
    |  IDENT '(' Arguments  ')' ';'
    |  RETURN Exp ';'
    |  RETURN ';'
    |  '{' SuiteInstr '}'
    |  ';'
    ;
Exp :  Exp OR TB
    |  TB
    ;
TB  :  TB AND FB
    |  FB
    ;
FB  :  FB EQ M
    |  M
    ;
M   :  M ORDER E
    |  E
    ;
E   :  E ADDSUB T
    |  T
    ;    
T   :  T DIVSTAR F 
    |  F
    ;
F   :  ADDSUB F
    |  '!' F
    |  '(' Exp ')'
    |  NUM
    |  CHARACTER
    |  IDENT
    |  IDENT '(' Arguments  ')'
    ;
Arguments:
       ListExp
    |
    ;
ListExp:
       ListExp ',' Exp
    |  Exp
    ;
%%
