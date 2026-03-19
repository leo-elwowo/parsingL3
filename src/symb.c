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

void insert_on_bucket_head(Bucket * bucket, Symbol * sym){
    Bucket tmp = (Bucket)malloc(sizeof(Node));
    if (!tmp) return 1;
    tmp->val = sym;
    tmp->prochain = bucket;
    *bucket = tmp;
    return 0;
}

int init_table(HashTable ** tab){
    *tab = (HashTable *)malloc(sizeof(HashTable));
    if (!(*tab)) return 1;
    (*tab)->size = 0;
    (*tab)->cap = N;
    return 0;
}

static int check_if_present(const Bucket bucket, const char * ident){
    Bucket tmp = bucket;
    while (tmp){
        if (strcmp(tmp->val->ident, ident) == 0){
            return 0;//present
        }
        tmp = tmp->prochain;
    }
    return 1; //pas présent
}

void insert_value(const char * ident,const Type type, HashTable tab[]){
    int index = 0;
    while (index < tab->size){
        printf("current table = table %d\n", index);
        if (check_if_present){
            index++;
            continue;
        }
        else{
            Symbol * ajt = NULL;
            init_symbol(ajt, ident, type);
            insert_on_bucket_head(tab->elt, ajt);
        }
    }
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

