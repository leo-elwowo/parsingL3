#include "symb.h"
#include "sem.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int init_symbol(Symbol ** sym, const char * ident, Type type, int deplct){
    *sym = (Symbol *)malloc(sizeof(Symbol));
    if (!(*sym)) return 1;
    strcpy((*sym)->ident, ident);
    (*sym)->type = type;
    (*sym)->deplct = deplct;//on verra plus tard mdr
    return 0;
}

static unsigned int hfunc(const char * ident){
    unsigned long long h = 0;   //il faut que h puisse etre tres tres grand
                                //parce qu'on multiplie par K a chaque caractère
    for (int i = 0; ident[i] != '\0'; i++){
        h = K * h + ident[i];
    }
    unsigned int rtrn = (h % 1073741824) % N;
    return rtrn;
}



static int insert_on_bucket_head(Bucket * bucket, Symbol * sym){
    Bucket tmp = (Bucket)malloc(sizeof(SymNode));
    if (!tmp) return 1;
    tmp->val = sym;
    tmp->prochain = *bucket;
    *bucket = tmp;
    return 0;
}

int init_table(HashTable ** tab){
    *tab = (HashTable *)malloc(sizeof(HashTable));
    if (!(*tab)) return 1;
    (*tab)->size = 0;
    (*tab)->cap = N;
    for(int i = 0; i < N; i++){
        (*tab)->elt[i] = NULL;
    }
    return 0;
}

static Symbol * check_if_present_and_move_to_head_then(Bucket * bucket, const char * ident){
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

Symbol* search_value(const char * ident, HashTable * tab) {
    if (tab == NULL) return NULL;
    unsigned int hf_index = hfunc(ident);
    return check_if_present_and_move_to_head_then(&tab->elt[hf_index], ident);
}

void insert_value(const char * ident,const Type type, int deplct, HashTable * tab){
    /*
    tant qu'on a pas programmé la table de hashage, on va juste prendre dans l'ordre
    avec un index
    edit : c'est fait :))
    */
    unsigned int hf_index = hfunc(ident);
    
    if (check_if_present_and_move_to_head_then (&tab->elt[hf_index], ident) == NULL){
        Symbol * ajt = NULL;
        init_symbol(&ajt, ident, type, deplct);
        insert_on_bucket_head(&tab->elt[hf_index], ajt);
        tab->size++;
    }
    else fprintf(stderr,"nothing inserted, value already present....\n");
}

static void free_bucket(Bucket bucket){
    Bucket tmp = bucket;
    Bucket freeer;
    while (tmp){
        freeer = tmp;
        tmp = tmp->prochain;
        free(freeer->val);
        free(freeer);
        
    }   
}

void free_table(HashTable * tab){
    for (int i = 0; i < tab->cap; i++){
        free_bucket(tab->elt[i]);
    }
    free(tab);
}
/*
admettons..
int main(void){
    HashTable * table;
    init_table(&table);
    insert_value("abcd", TYPE_CHAR, table);
}
*/
