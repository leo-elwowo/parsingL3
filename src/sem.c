#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "symb.h"

HashTable *global_table = NULL;
HashTable *local_table = NULL;
int current_offset = 0; 

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

        case T_DECL_VARS: {

            Node *type_node = node->firstChild;
            if (type_node == NULL || type_node->label != T_TYPE) break;


            Type current_type = TYPE_INT; // Par defaut


            HashTable *target_table = (local_table != NULL) ? local_table : global_table;

            Node *var_node = type_node->nextSibling;
            while (var_node != NULL) {
                if (var_node->label == T_IDENT) {
                    insert_value(var_node->ident, current_type, current_offset, target_table);
                    current_offset -= 8;
                }
                var_node = var_node->nextSibling;
            }
            break;
        }

        case T_PARAM: {
            Node *type_node = node->firstChild;
            Node *var_node = type_node != NULL ? type_node->nextSibling : NULL;
        
            if (var_node != NULL && var_node->label == T_IDENT) {
                insert_value(var_node->ident, TYPE_INT, current_offset, local_table);
                current_offset -= 8;
            }
            break;
        }

        case T_IDENT: {
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

        default:
            break;
    }

    if (node->label != T_DECL_VARS && node->label != T_PARAM) {
        for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
            analyze_semantics(child);
        }
    }

    if (node->label == T_FUNC) {
        // free_table(local_table); 
        // local_table = NULL;
    }
}