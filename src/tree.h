/* tree.h */
#ifndef TREE
#define TREE
typedef enum {
  PROG, 
  DECL_VARS, 
  DECL_FONCTS,
  FUNC, HEADER, 
  BODY, PARAM,
  INSTR_LIST, 
  IF, 
  WHILE, 
  RETURN, 
  ASSIGN, 
  FCALL,
  OR, 
  AND, 
  EQ, 
  ORDER, 
  ADDSUB, 
  DIVSTAR, 
  NOT,
  IDENT, 
  NUM, 
  CHARACTER, 
  TYPE,
  STRUCT_DECL, 
  MEMBER_ACCESS, 
  TYPE_STRUCT,
  LIST
  /* list all other node labels, if any */
  /* The list must coincide with the string array in tree.c */
  /* To avoid listing them twice, see https://stackoverflow.com/a/10966395 */
} label_t;

typedef struct Node {
  label_t label;
  int lineno;
  struct Node *firstChild, *nextSibling;
} Node;

Node *makeNode(label_t label);
void addSibling(Node *node, Node *sibling);
void addChild(Node *parent, Node *child);
void deleteTree(Node*node);
void printTree(Node *node);

#define FIRSTCHILD(node) node->firstChild
#define SECONDCHILD(node) node->firstChild->nextSibling
#define THIRDCHILD(node) node->firstChild->nextSibling->nextSibling
#endif