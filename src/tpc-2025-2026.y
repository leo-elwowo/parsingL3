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

/* Tokens Bison (Sans T_) */
%token <num> NUM
%token <ident> IDENT TYPE
%token <character> CHARACTER
%token <byte> ADDSUB DIVSTAR
%token <comp> EQ ORDER
%token IF ELSE WHILE RETURN STRUCT VOID AND OR

%type <node> Prog DeclVars DeclFoncts DeclFonct EnTeteFonct Parametres ListTypVar
%type <node> Corps SuiteInstr Instr Exp TB FB M E T F Arguments ListExp
%type <node> DeclStructs DeclStruct TypeName LValue Declarateurs

%%
Prog:  DeclStructs DeclVars DeclFoncts
    {
        root = makeNode(T_PROG);
        addChild(root, $1);
        addChild(root, $2);
        addChild(root, $3); 
    }
    ;

DeclStructs:
        DeclStructs DeclStruct 
        { 
           $$ = $1;
           if ($$ == NULL) $$ = makeNode(T_LIST);
           addChild($$, $2); 
        }
    |  { $$ = NULL; }
    ;

DeclStruct:
       STRUCT IDENT '{' DeclVars '}' ';'
       {
           $$ = makeNode(T_STRUCT_DECL);
           Node *nId = makeNode(T_IDENT); strcpy(nId->ident, $2);
           addChild($$, nId);
           addChild($$, $4); 
       }
    ;

DeclVars:
       DeclVars TypeName Declarateurs ';'
       {
           $$ = $1;
           if ($$ == NULL) $$ = makeNode(T_DECL_VARS);
        
           Node *groupe = makeNode(T_LIST);
           addChild(groupe, $2);
           addChild(groupe, $3);
           
           addChild($$, groupe);
       }
    | { $$ = NULL; }
    ;

Declarateurs:
       Declarateurs ',' IDENT
       {
           $$ = $1;
           Node *id = makeNode(T_IDENT); strcpy(id->ident, $3);
           addChild($$, id);
       }
    |
       IDENT
    {
        $$ = makeNode(T_LIST); 
        Node *id = makeNode(T_IDENT);
        strcpy(id->ident, $1);
        addChild($$, id);
    }
    ;

TypeName:
       TYPE 
       { 
           $$ = makeNode(T_TYPE);
           strcpy($$->ident, $1);
       }
    |  STRUCT IDENT
       {
           $$ = makeNode(T_TYPE_STRUCT);
           Node *id = makeNode(T_IDENT); strcpy(id->ident, $2);
           addChild($$, id);
       }
    ;

DeclFoncts:
       DeclFoncts DeclFonct
       {
           $$ = $1;
           if ($$ == NULL) $$ = makeNode(T_DECL_FONCTS);
           addChild($$, $2);
       }
    |
       DeclFonct
       {
           $$ = makeNode(T_DECL_FONCTS);
           addChild($$, $1);
       }
    ;

DeclFonct:
       EnTeteFonct Corps
       {
           $$ = makeNode(T_FUNC);
           addChild($$, $1);
           addChild($$, $2);
       }
    ;

EnTeteFonct:
       TypeName IDENT '(' Parametres ')'
       {
           $$ = makeNode(T_HEADER);
           addChild($$, $1); 
           Node *id = makeNode(T_IDENT); strcpy(id->ident, $2);
           addChild($$, id);
           addChild($$, $4); 
       }
    |
       VOID IDENT '(' Parametres ')'
       {
           $$ = makeNode(T_HEADER);
           Node *v = makeNode(T_TYPE); strcpy(v->ident, "void");
           addChild($$, v);
           Node *id = makeNode(T_IDENT); strcpy(id->ident, $2);
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
           Node *p = makeNode(T_PARAM);
           addChild(p, $3);
           Node *id = makeNode(T_IDENT); strcpy(id->ident, $4);
           addChild(p, id);
           addChild($$, p);
       }
    |  TypeName IDENT
       {
           $$ = makeNode(T_LIST);
           Node *p = makeNode(T_PARAM);
           addChild(p, $1);
           Node *id = makeNode(T_IDENT); strcpy(id->ident, $2);
           addChild(p, id);
           addChild($$, p);
       }
    ;

Corps: '{' DeclVars SuiteInstr '}'
    {
        $$ = makeNode(T_BODY);
        addChild($$, $2); 
        addChild($$, $3);
    }
    ;

SuiteInstr:
       SuiteInstr Instr
       {
           $$ = $1;
           if ($$ == NULL) $$ = makeNode(T_INSTR_LIST);
           addChild($$, $2);
       }
    |  { $$ = NULL; }
    ;

Instr:
       LValue '=' Exp ';'
       {
           $$ = makeNode(T_ASSIGN);
           addChild($$, $1);
           addChild($$, $3);
       }
    |  IF '(' Exp ')' Instr
       {
           $$ = makeNode(T_IF);
           addChild($$, $3);
           addChild($$, $5);
       }
    |  IF '(' Exp ')' Instr ELSE Instr
       {
           $$ = makeNode(T_IF);
           addChild($$, $3);
           addChild($$, $5);
           addChild($$, $7);
       }
    |
       WHILE '(' Exp ')' Instr
       {
           $$ = makeNode(T_WHILE);
           addChild($$, $3);
           addChild($$, $5);
       }
    |  IDENT '(' Arguments  ')' ';'
       {
           $$ = makeNode(T_FCALL);
           Node *id = makeNode(T_IDENT); strcpy(id->ident, $1);
           addChild($$, id);
           addChild($$, $3);
       }
    |  RETURN Exp ';'
       {
           $$ = makeNode(T_RETURN);
           addChild($$, $2);
       }
    |  RETURN ';' { $$ = makeNode(T_RETURN); }
    |
       '{' SuiteInstr '}' { $$ = $2; }
    |  ';' { $$ = NULL; }
    ;

LValue:
       IDENT 
       { 
           $$ = makeNode(T_IDENT);
           strcpy($$->ident, $1); 
       }
    |  LValue '.' IDENT
       {
           $$ = makeNode(T_MEMBER_ACCESS);
           addChild($$, $1); 
           Node *id = makeNode(T_IDENT); strcpy(id->ident, $3);
           addChild($$, id);
       }
    ;

Exp :  Exp OR TB 
       { $$ = makeNode(T_OR); addChild($$, $1);
         addChild($$, $3); }
    |  TB { $$ = $1; }
    ;

TB  :  TB AND FB 
       { $$ = makeNode(T_AND); addChild($$, $1);
         addChild($$, $3); }
    |  FB { $$ = $1; }
    ;

FB  :  FB EQ M 
       { 
           $$ = makeNode(T_EQ);
           strcpy($$->comp, $2); 
           addChild($$, $1); addChild($$, $3); 
       }
    |  M { $$ = $1; }
    ;

M   :  M ORDER E 
       { 
           $$ = makeNode(T_ORDER);
           strcpy($$->comp, $2); 
           addChild($$, $1); addChild($$, $3); 
       }
    |  E { $$ = $1; }
    ;

E   :  E ADDSUB T 
       { 
           $$ = makeNode(T_ADDSUB);
           $$->byte = $2;
           addChild($$, $1); addChild($$, $3); 
       }
    |  T { $$ = $1; }
    ; 

T   :  T DIVSTAR F 
       { 
           $$ = makeNode(T_DIVSTAR);
           $$->byte = $2; 
           addChild($$, $1); addChild($$, $3); 
       }
    |  F { $$ = $1; }
    ;

F   :  ADDSUB F
       {
           $$ = makeNode(T_ADDSUB);
           $$->byte = $1; 
           addChild($$, $2);
       }
    |  '!' F
       {
           $$ = makeNode(T_NOT);
           addChild($$, $2);
       }
    |  '(' Exp ')' { $$ = $2; }
    |
       NUM 
       { 
           $$ = makeNode(T_NUM);
           $$->num = $1; 
       }
    |  CHARACTER
       {
           $$ = makeNode(T_CHARACTER);
           $$->character = $1;
       }
    |  LValue 
       { $$ = $1; }
    |  IDENT '(' Arguments  ')'
       {
           $$ = makeNode(T_FCALL);
           Node *id = makeNode(T_IDENT); strcpy(id->ident, $1);
           addChild($$, id);
           addChild($$, $3);
       }
    ;

Arguments:
       ListExp { $$ = $1; }
    |
       { $$ = NULL; }
    ;

ListExp:
       ListExp ',' Exp
       {
           $$ = $1;
           if ($$ == NULL) $$ = makeNode(T_LIST);
           addChild($$, $3);
       }
    |
       Exp
       {
           $$ = makeNode(T_LIST);
           addChild($$, $1);
       }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erreur ligne %d : %s\n", lineno, s);
}

int main(int argc, char **argv) {
    int print = 0;
    if (argc > 1 && (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "--tree") == 0)) print = 1;
    if (yyparse() == 0) {
        return 0;
    }
    if (print && root != NULL) {
            printTree(root);
        }
    return 1;
}