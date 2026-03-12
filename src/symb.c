#include "symb.h"
#include <stdlib.h>
#include <string.h>

int init_symbol(Symbol ** sym, char * ident, Type type){
    *sym = (Symbol *)malloc(sizeof(Symbol));
    if (!(*sym)) return 1;
    strcpy((*sym)->ident, ident);
    (*sym)->type = type;
    return 0;
}

int init_bucket(Bucket * bucket, Symbol * sym){
    bucket = (Bucket *)malloc(sizeof(Bucket));
    if (!bucket) return 1;
    (*bucket)->val = sym;
    (*bucket)->prochain = NULL;
    return 0;
}

int init_table(HashTable ** tab){
    *tab = (HashTable *)malloc(sizeof(HashTable));
    if (!(*tab)) return 1;
    (*tab)->size = 0;
    (*tab)->cap = N;
    return 0;
}

static void free_bucket(Bucket * bucket){
    Bucket tmp = (*bucket);
    Bucket freeer;
    while (tmp){
        freeer = tmp;
        free(freeer->val);
        free(freeer);
        tmp = tmp->prochain;
    }
    free(bucket);
}

void free_table(HashTable * tab){
    for (int i = 0; i < tab->size; i++){
        free_bucket(tab->elt[i]);
    }
}
