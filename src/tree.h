/* tree.h */
#ifndef TREE
#define TREE
typedef enum {
  T_PROG, 
  T_DECL_VARS, 
  T_DECL_FONCTS,
  T_FUNC, 
  T_HEADER, 
  T_BODY, 
  T_PARAM,
  T_INSTR_LIST, 
  T_IF, 
  T_WHILE, 
  T_RETURN, 
  T_ASSIGN, 
  T_FCALL,
  T_OR, 
  T_AND, 
  T_EQ, 
  T_ORDER, 
  T_ADDSUB, 
  T_DIVSTAR, 
  T_NOT,
  T_IDENT, 
  T_NUM, 
  T_CHARACTER, 
  T_TYPE,
  T_STRUCT_DECL, 
  T_MEMBER_ACCESS, 
  T_TYPE_STRUCT,
  T_LIST,
  T_VOID
} label_t;

typedef struct Node {
  label_t label;
  int lineno;
  struct Node *firstChild, *nextSibling;
  char ident[64];
  int num; 
  char byte;
  char character;
  char comp[4];
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