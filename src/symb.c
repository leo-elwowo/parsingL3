#include "symb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

int insert_on_bucket_head(Bucket * bucket, Symbol * sym){
    if (!bucket){
        int rt = init_bucket(bucket, sym);
        if (rt == 1) return 1;
        return 2; 
        /*
        on renvoit 2 dans le cas spécial ou l'on insère la première valeur d'un
        des buckets.
        */
    }
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

void insert_value(const char * ident,const Type type, HashTable * tab, int index){
    /*
    tant qu'on a pas programmé la table de hashage, on va juste prendre dans l'ordre
    avec un index
    
    */
    Symbol * ajt = NULL;
    init_symbol(&ajt, ident, type);
    if (!check_if_present(tab->elt[index], ident)){
        insert_on_bucket_head(&tab->elt[index], ajt);
    }
    else printf("nothing inserted, value already present....\n");
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

int main(void){
    HashTable * table;
    init_table(&table);
    insert_value("abcd", TYPE_CHAR, table, 0);
}