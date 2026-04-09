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
}Node, *Bucket;



typedef struct _hashtab{
    /*
    on rajoutera une fonction plus tard pour en faire une table de hashage 
    edit : c'est fait
    */
    Bucket elt[N];
    int size;
    int cap;
}HashTable;

#endif