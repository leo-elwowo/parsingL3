#ifndef SYMBOLS
#define SYMBOLS
#include "identsize.h"
#define N 1008
#define K 613

typedef enum _type{
    TYPE_INT,
    TYPE_CHAR
} Type;

typedef struct _symb{
    char ident[MAX_IDENTSIZE];
    Type type;
    int deplct;
}Symbol;

typedef struct _bucket{
    Symbol * val;
    struct _bucket * prochain;
}SymNode, *Bucket;

typedef struct _hashtab{
    /*
    on rajoutera une fonction plus tard pour en faire une table de hashage 
    edit : c'est fait
    */
    Bucket elt[N];
    int size;
    int cap;
}HashTable;

int init_table(HashTable ** tab);
int init_symbol(Symbol ** sym, const char * ident, Type type, int deplct);

void insert_value(const char * ident, const Type type, int deplct, HashTable * tab);
Symbol* search_value(const char * ident, HashTable * tab);

void free_table(HashTable * tab);

#endif