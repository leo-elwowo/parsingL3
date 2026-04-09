#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "symb.h"

HashTable *global_table = NULL;
HashTable *local_table = NULL;
int current_offset = 0; 
extern int printsymb;
extern FILE * nasm_output;


void sem(Node *node) {
    
    if (node == NULL) return;
    switch (node->label) {
        case T_PROG:
            init_table(&global_table);
            break;

        case T_FUNC:
            init_table(&local_table);
            
            current_offset = 0; 
            break;
        case T_DECL_VARS: 
        {
            Node *list1 = node->firstChild;
            if (list1 == NULL || list1->label != T_LIST) break;

            Node *type_node = list1->firstChild;
            if (type_node == NULL || (type_node->label != T_TYPE && type_node->label != T_TYPE_STRUCT)) break;

            Type current_type = TYPE_INT;
            HashTable *target_table = (local_table != NULL) ? local_table : global_table;


            Node *list2 = type_node->nextSibling;
            if (list2 != NULL && list2->label == T_LIST) {
                Node *var_node = list2->firstChild;
                
                while (var_node != NULL) {
                    if (var_node->label == T_IDENT) {
                        insert_value(var_node->ident, current_type, current_offset, target_table);
                        current_offset -= 8;
                    }
                    var_node = var_node->nextSibling;
                }
            }
            break;
        }

        case T_PARAM: 
        {
            Node *type_node = node->firstChild;
            Node *var_node = type_node != NULL ? type_node->nextSibling : NULL;
            if (var_node != NULL && var_node->label == T_IDENT) {
                insert_value(var_node->ident, TYPE_INT, current_offset, local_table);
                current_offset -= 8;
            }
            break;
        }

        case T_IDENT: 
        {
            Symbol *found = NULL;
            found = search_value(node->ident, local_table);
            if (found == NULL) {
                found = search_value(node->ident, global_table);
            }
            if (found == NULL) {
                fprintf(stderr, "Erreur sémantique : variable '%s' non déclarée (ligne %d)\n", node->ident, node->lineno);
            }
            break;
        }

        case T_MEMBER_ACCESS:

            if (node->firstChild != NULL) {
                sem(node->firstChild);
            }
            break;

        case T_FCALL:
            if (node->firstChild != NULL && node->firstChild->nextSibling != NULL) {
                sem(node->firstChild->nextSibling);
            }
            break;

        case T_STRUCT_DECL:

            break;
        
        default:
            break;
    }

    if (node->label != T_DECL_VARS && node->label != T_PARAM && node->label != T_HEADER 
        && node->label != T_MEMBER_ACCESS && node->label != T_FCALL && node->label != T_STRUCT_DECL) {
        
        for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
            if (child->label == T_ASSIGN){
                printf("ASSIGN\n");
            }
            sem(child);
        }
    }

    if (node->label == T_HEADER) {
        //printf("name of func : %s\n", node->firstChild->nextSibling->ident);
        /*
        the HEADER node contains the header of a function, so its name and its return type

        here we check the name of the function contained
        in node->firstChild->nextSibling->ident
        if the name of the function is main, we write the basic asm instructions
        */
        if (!strcmp(node->firstChild->nextSibling->ident, "main")){
            fwrite("global _start\nsection .text\nstart:\n",sizeof(char), 35, nasm_output );
            fwrite( "mov rax, 60\nmov rdi, 0\nsyscall\n", sizeof(char), 31,nasm_output);
        }
        for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
            if (child->label != T_IDENT && child->label != T_TYPE) {
                sem(child);
            }
        }
    }


    if (node->label == T_FUNC) {
        // free_table(local_table); 
        // local_table = NULL;
    }

    if (printsymb) {
        if (node->label == T_PROG) {
            print_table(global_table, "Variables Globales");
        }
        if (node->label == T_FUNC) {
            print_table(local_table, "Variables Locales (Fonction)");
        }
    }
}