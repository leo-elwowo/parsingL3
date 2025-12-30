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
%token <ident> IDENT TYPE
%token <character> CHARACTER
%token <byte> ADDSUB DIVSTAR
%token <comp> EQ ORDER
%token IF ELSE WHILE RETURN STRUCT VOID AND OR

%type <node> Prog DeclVars DeclFoncts DeclFonct EnTeteFonct Parametres ListTypVar
%type <node> Corps SuiteInstr Instr Exp TB FB M E T F Arguments ListExp
%type <node> DeclStructs DeclStruct TypeName LValue

%%
Prog:  DeclStructs DeclVars DeclFoncts
    {
        root = makeNode(PROG);
        addChild(root, $1);
        addChild(root, $2);
        addChild(root, $3); 
    }
    ;
DeclStructs:
        DeclStructs DeclStruct 
        { 
           $$ = $1; 
           if ($$ == NULL) $$ = makeNode(LIST);
           addChild($$, $2); 
        }
    |  { $$ = NULL; }
    ;

DeclStruct:
       STRUCT IDENT '{' DeclVars '}' ';'
       {
           $$ = makeNode(STRUCT_DECL);
           Node *nId = makeNode(IDENT); strcpy(nId->ident, $2);
           addChild($$, nId);
           addChild($$, $4); /* Les champs */
       }
    ;
DeclVars:
       DeclVars TypeName Declarateurs ';'
       {
           $$ = $1;
           if ($$ == NULL) $$ = makeNode(DECL_VARS);
        
           Node *groupe = makeNode(LIST);
           addChild(groupe, $2); /* Le type */
           addChild(groupe, $3); /* Les variables */
           
           addChild($$, groupe);
       }
    | { $$ = NULL; }
    ;
Declarateurs:
       Declarateurs ',' IDENT
       {
           $$ = $1;
           Node *id = makeNode(IDENT); strcpy(id->ident, $3);
           addChild($$, id);
       }
    |  IDENT
    {
        $$ = makeNode(LIST); 
        Node *id = makeNode(IDENT); strcpy(id->ident, $1);
        addChild($$, id);
    }
    ;
TypeName:
       TYPE 
       { 
           $$ = makeNode(TYPE);
           strcpy($$->ident, $1); 
       }
    |  STRUCT IDENT
       {
           $$ = makeNode(TYPE_STRUCT);
           Node *id = makeNode(IDENT); strcpy(id->ident, $2);
           addChild($$, id);
       }
    ;
DeclFoncts:
       DeclFoncts DeclFonct
       {
           $$ = $1;
           if ($$ == NULL) $$ = makeNode(DECL_FONCTS);
           addChild($$, $2);
       }
    |  DeclFonct
       {
           $$ = makeNode(DECL_FONCTS);
           addChild($$, $1);
       }
    ;
DeclFonct:
       EnTeteFonct Corps
       {
           $$ = makeNode(FUNC);
           addChild($$, $1);
           addChild($$, $2);
       }
    ;
EnTeteFonct:
       TypeName IDENT '(' Parametres ')'
       {
           $$ = makeNode(HEADER);
           addChild($$, $1); 
           Node *id = makeNode(IDENT); strcpy(id->ident, $2);
           addChild($$, id);
           addChild($$, $4); 
       }
    |  VOID IDENT '(' Parametres ')'
       {
           $$ = makeNode(HEADER);
           Node *v = makeNode(TYPE); strcpy(v->ident, "void");
           addChild($$, v);
           Node *id = makeNode(IDENT); strcpy(id->ident, $2);
           addChild($$, id);
           addChild($$, $4);
       }
    ;
Parametres:
       VOID { $$ = NULL; }
    |  ListTypVar { $$ = $1; }
    ;
ListTypVar:
       ListTypVar ',' TypeName IDENT
       {
           $$ = $1;
           Node *p = makeNode(PARAM);
           addChild(p, $3);
           Node *id = makeNode(IDENT); strcpy(id->ident, $4);
           addChild(p, id);
           addChild($$, p);
       }
    |  TypeName IDENT
       {
           $$ = makeNode(LIST);
           Node *p = makeNode(PARAM);
           addChild(p, $1);
           Node *id = makeNode(IDENT); strcpy(id->ident, $2);
           addChild(p, id);
           addChild($$, p);
       }
    ;
Corps: '{' DeclVars SuiteInstr '}'
    {
        $$ = makeNode(BODY);
        addChild($$, $2); /* Var locales */
        addChild($$, $3); /* Instructions */
    }
    ;
SuiteInstr:
       SuiteInstr Instr
       {
           $$ = $1;
           if ($$ == NULL) $$ = makeNode(INSTR_LIST);
           addChild($$, $2);
       }
    |  { $$ = NULL; }
    ;
Instr:
       LValue '=' Exp ';' 
       {
           $$ = makeNode(ASSIGN);
           addChild($$, $1);
           addChild($$, $3);
       }
    |  IF '(' Exp ')' Instr
       {
           $$ = makeNode(IF);
           addChild($$, $3);
           addChild($$, $5);
       }
    |  IF '(' Exp ')' Instr ELSE Instr
       {
           $$ = makeNode(IF);
           addChild($$, $3);
           addChild($$, $5);
           addChild($$, $7);
       }
    |  WHILE '(' Exp ')' Instr
       {
           $$ = makeNode(WHILE);
           addChild($$, $3);
           addChild($$, $5);
       }
    |  IDENT '(' Arguments  ')' ';'
       {
           $$ = makeNode(FCALL);
           Node *id = makeNode(IDENT); strcpy(id->ident, $1);
           addChild($$, id);
           addChild($$, $3);
       }
    |  RETURN Exp ';'
       {
           $$ = makeNode(RETURN);
           addChild($$, $2);
       }
    |  RETURN ';' { $$ = makeNode(RETURN); }
    |  '{' SuiteInstr '}' { $$ = $2; }
    |  ';' { $$ = NULL; }
    ;
LValue:
       IDENT 
       { 
           $$ = makeNode(IDENT); strcpy($$->ident, $1); 
       }
    |  LValue '.' IDENT
       {
           $$ = makeNode(MEMBER_ACCESS);
           addChild($$, $1); 
           Node *id = makeNode(IDENT); strcpy(id->ident, $3);
           addChild($$, id);
       }
    ;
Exp :  Exp OR TB 
       { $$ = makeNode(OR); addChild($$, $1); addChild($$, $3); }
    |  TB { $$ = $1; }
    ;

TB  :  TB AND FB 
       { $$ = makeNode(AND); addChild($$, $1); addChild($$, $3); }
    |  FB { $$ = $1; }
    ;
FB  :  FB EQ M 
       { 
           $$ = makeNode(EQ); 
           strcpy($$->comp, $2); 
           addChild($$, $1); addChild($$, $3); 
       }
    |  M { $$ = $1; }
    ;
M   :  M ORDER E 
       { 
           $$ = makeNode(ORDER); 
           strcpy($$->comp, $2); 
           addChild($$, $1); addChild($$, $3); 
       }
    |  E { $$ = $1; }
    ;
E   :  E ADDSUB T 
       { 
           $$ = makeNode(ADDSUB); 
           $$->byte = $2;
           addChild($$, $1); addChild($$, $3); 
       }
    |  T { $$ = $1; }
    ; 
T   :  T DIVSTAR F 
       { 
           $$ = makeNode(DIVSTAR); 
           $$->byte = $2; 
           addChild($$, $1); addChild($$, $3); 
       }
    |  F { $$ = $1; }
    ;
F   :  ADDSUB F
       {
           $$ = makeNode(ADDSUB);
           $$->byte = $1; 
           addChild($$, $2);
       }
    |  '!' F
       {
           $$ = makeNode(NOT);
           addChild($$, $2);
       }
    |  '(' Exp ')' { $$ = $2; }
    |  NUM 
       { 
           $$ = makeNode(NUM); 
           $$->num = $1; 
       }
    |  CHARACTER
       {
           $$ = makeNode(CHARACTER);
           $$->character = $1;
       }
    |  LValue 
       { $$ = $1; }
    |  IDENT '(' Arguments  ')'
       {
           $$ = makeNode(FCALL);
           Node *id = makeNode(IDENT); strcpy(id->ident, $1);
           addChild($$, id);
           addChild($$, $3);
       }
    ;
Arguments:
       ListExp { $$ = $1; }
    |  { $$ = NULL; }
    ;
ListExp:
       ListExp ',' Exp
       {
           $$ = $1;
           if ($$ == NULL) $$ = makeNode(LIST);
           addChild($$, $3);
       }
    |  Exp
       {
           $$ = makeNode(LIST);
           addChild($$, $1);
       }
    ;
%%
void yyerror(const char *s) {
    fprintf(stderr, "Erreur ligne %d : %s\n", lineno, s);
}

int main(int argc, char **argv) {
    int print = 0;
    if (argc > 1 && strcmp(argv[1], "-t") == 0) print = 1;

    if (yyparse() == 0) {
        if (print && root != NULL) {
            printTree(root);
        }
        return 0;
    }
    return 1;
}