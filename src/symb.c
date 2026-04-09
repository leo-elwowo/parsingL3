#include "symb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int init_symbol(Symbol ** sym, const char * ident, Type type){
    *sym = (Symbol *)malloc(sizeof(Symbol));
    if (!(*sym)) return 1;
    strcpy((*sym)->ident, ident);
    (*sym)->type = type;
    return 0;
}

int init_bucket(Bucket * bucket, Symbol * sym){
    *bucket = (Bucket)malloc(sizeof(Node));
    if (!(*bucket)) return 1;
    (*bucket)->val = sym;
    (*bucket)->prochain = NULL;
    return 0;
}

unsigned int hfunc(const char * ident){
    unsigned long long h = 0;   //il faut que h puisse etre tres tres grand
                                //parce qu'on multiplie par K a chaque caractère
    for (int i = 0; ident[i] != '\0'; i++){
        h = K * h + ident[i];
    }
    unsigned int rtrn = (h % 1073741824) % N;
    return rtrn;
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

Symbol * check_if_present_and_move_to_head_then(Bucket * bucket, const char * ident){
    //bucket pointer parce qu'on pourrait le remettre en tete l'ident
    Bucket prev = NULL;
    Bucket curr = *bucket;

    while (curr) {
        if (strcmp(curr->val->ident, ident) == 0) {
            // Si l'élément est trouvé et n'est pas déjà en tête
            if (prev != NULL) {
                // Détacher l'élément de sa position actuelle
                prev->prochain = curr->prochain;
                // Le placer au tout début (en tête)
                curr->prochain = *bucket;
                *bucket = curr;
            }
            return curr->val; // Symbole trouvé
        }
        prev = curr;
        curr = curr->prochain;
    }
    return NULL; // Pas présent
}

void insert_value(const char * ident,const Type type, HashTable * tab){
    /*
    tant qu'on a pas programmé la table de hashage, on va juste prendre dans l'ordre
    avec un index
    edit : c'est fait :))
    */
    unsigned int hf_index = hfunc(ident);
    
    if (!check_if_present(tab->elt[hf_index], ident)){
        Symbol * ajt = NULL;
        init_symbol(&ajt, ident, type);
        insert_on_bucket_head(&tab->elt[hf_index], ajt);
    }
    else fprintf(stderr,"nothing inserted, value already present....\n");
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
    insert_value("abcd", TYPE_CHAR, table);
}