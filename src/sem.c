#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "symb.h"
#include "sem.h"

HashTable *global_table = NULL;
HashTable *local_table = NULL;
int current_offset = 0; 
extern int printsymb;
extern FILE * nasm_output;

static const char *StringFromLabel_suppr_juste_pour_print[] = {
    /*
    j'ai recopié ca depuis le tree.c c'est juste pour que je puisse
    l'utiliser pour voir quels types de noeuds je parcours*/
  "PROG", 
  "DECL_VARS", 
  "DECL_FONCTS",
  "FUNC", 
  "HEADER", 
  "BODY", 
  "PARAM",
  "INSTR_LIST", 
  "IF", 
  "WHILE", 
  "RETURN", 
  "ASSIGN", 
  "FCALL",
  "OR", 
  "AND", 
  "EQ", 
  "ORDER", 
  "ADDSUB", 
  "DIVSTAR", 
  "NOT",
  "IDENT", 
  "NUM", 
  "CHARACTER", 
  "TYPE",
  "TAB",
  "STRUCT_DECL", 
  "MEMBER_ACCESS", 
  "TYPE_STRUCT",
  "LIST",
  "VOID"
};



static int newlabel(){
    static int i = 0;
    return ++i;
}

static void write_asm_bool(FILE *file, Node *node, int label_true, int label_false);
//parce que sinon write_asm_expr ne la trouvera pas

static void write_asm_expr(FILE * file, Node * node){
    if (!node)
        return;
    
    switch (node->label) {
        /*
        case T_RETURN:
        
        break;
        */
        case T_EQ:
        case T_ORDER:
        case T_AND:
        case T_OR:
        case T_NOT: {
            int label_true = newlabel();
            int label_false = newlabel();
            int label_fin = newlabel();

            // 1. On confie l'évaluation paresseuse à notre fonction dédiée
            write_asm_bool(file, node, label_true, label_false);

            // 2. Si l'expression atterrit ici, c'est VRAI : on empile 1
            fprintf(file, ".L%d:\n", label_true);
            fprintf(file, "\tpush 1\n");
            fprintf(file, "\tjmp .L%d\n", label_fin); // On saute à la fin

            // 3. Si l'expression atterrit ici, c'est FAUX : on empile 0
            fprintf(file, ".L%d:\n", label_false);
            fprintf(file, "\tpush 0\n");

            // 4. Point de chute final pour que le calcul reprenne
            fprintf(file, ".L%d:\n", label_fin);
            break;
        }
        case T_NUM:
        fprintf(file, "\t;mise sur la pile du nombre '%d'\n", node->num);
        fprintf(file, "\tpush %d\n", node->num);
        break;
        case T_CHARACTER:
        fprintf(file, "\t;mise sur la pile du caractère '%c'\n", node->character);
        fprintf(file, "\tpush %d\n", node->character);
        break;
        case T_ADDSUB:
        
        //si c'est une soustraction on fait ca
        //fprintf(file, "\t;on traite la soustraction\n");
        write_asm_expr(file, node->firstChild);    //on va push la partie gauche
        write_asm_expr(file, node->firstChild->nextSibling);    //push la droite
        //et apres on la depile dans rbx et rax
        fprintf(file, "\tpop rbx\n");
        fprintf(file, "\tpop rax\n");
        if (node->byte == '-'){
            fprintf(file, "\tsub rax, rbx\n");
        }
        else{
            fprintf(file, "\tadd rax, rbx\n");
        }
        fprintf(file, "\tpush rax\n");
        
        //note : faire le + asap
        break;
        case T_DIVSTAR:
        /*
        ici on va gérer l'écriture dans le programme des opérations * et /
        il faut le faire aussi
        */
        write_asm_expr(file, node->firstChild);    //on va push la partie gauche
        write_asm_expr(file, node->firstChild->nextSibling);    //push la droite
        //et apres on la depile dans rbx et rax
        fprintf(file, "\tpop rbx\n");
        fprintf(file, "\tpop rax\n");
        if (node->byte == '*'){
            //pour faire imul
            fprintf(file, "\timul rax, rbx\n");
            fprintf(file, "\tpush rax\n");    
        }
        else{

            //pour faire idiv, mais je suis pas sur que ce soit la bonne facon
            /*
            update après vérification ca marche mais il faut que le dividende soit positif
            */
            fprintf(file, "\txor rdx, rdx\n");
            fprintf(file, "\tidiv rbx\n");
            fprintf(file, "\tpush rax\n");    
        }
        
        break;
        case T_IDENT:
        Symbol *s_read = search_value(node->ident, local_table);
        if (s_read != NULL) {
            fprintf(file, "\tmov rax, [rbp%+d]\n", s_read->deplct);
            fprintf(file, "\tpush rax\n");
            break;
        }
        //si notre ident est une variable globale (donc presente dans la table des symboles)
        //on va faire ca
        s_read = search_value(node->ident, global_table);
        if (s_read != NULL) {
            fprintf(file, "\tmov rax, [%s]\n", s_read->ident);
            fprintf(file, "\tpush rax\n");
        }
        break;
        case T_FCALL: {
            char *func_name = node->firstChild->ident;
            Node *args_list = node->firstChild->nextSibling;
            int arg_count = 0;
            if (args_list != NULL && args_list->label == T_LIST) {
                for (Node *arg = args_list->firstChild; arg != NULL; arg = arg->nextSibling) {
                    write_asm_expr(file, arg);
                    arg_count++;
                }
            }
            const char* regs[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
            for (int i = arg_count - 1; i >= 0; i--) {
                fprintf(file, "\tpop %s\n", regs[i]);
            }
            fprintf(file, "\tcall %s\n", func_name);
            fprintf(file, "\tpush rax\n");
            break;
        }
        default:
        //ici c'est juste pr si nos enfants doivent etre parcourus
        for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
            write_asm_expr(file, child);
        }
        break;
    }
    return;
}

static void write_asm_bool(FILE *file, Node *node, int label_true, int label_false) {
    if (!node) return;

    switch (node->label) {
        case T_EQ:
            write_asm_expr(file, node->firstChild);
            write_asm_expr(file, node->firstChild->nextSibling);

            fprintf(file, "\tpop rbx\n");
            fprintf(file, "\tpop rax\n");
            fprintf(file, "\tcmp rax, rbx\n");
            if (strcmp(node->comp, "==") == 0) {
                fprintf(file, "\tje .L%d\n", label_true); 
            } else if (strcmp(node->comp, "!=") == 0) {
                fprintf(file, "\tjne .L%d\n", label_true);
            }
            fprintf(file, "\tjmp .L%d\n", label_false);
            break;
        case T_ORDER:
            write_asm_expr(file, node->firstChild);
            write_asm_expr(file, node->firstChild->nextSibling);
            
            fprintf(file, "\tpop rbx\n");
            fprintf(file, "\tpop rax\n");
            fprintf(file, "\tcmp rax, rbx\n");
            if (strcmp(node->comp, "<") == 0) {
                fprintf(file, "\tjl .L%d\n", label_true);  
            } else if (strcmp(node->comp, ">") == 0) {
                fprintf(file, "\tjg .L%d\n", label_true);  
            } else if (strcmp(node->comp, "<=") == 0) {
                fprintf(file, "\tjle .L%d\n", label_true);  
            } else if (strcmp(node->comp, ">=") == 0) {
                fprintf(file, "\tjge .L%d\n", label_true);  
            }
            fprintf(file, "\tjmp .L%d\n", label_false); 
            break;
        case T_NOT:
            write_asm_bool(file, node->firstChild, label_false, label_true);
            break;

        case T_AND: {
            int label_next = newlabel();
            write_asm_bool(file, node->firstChild, label_next, label_false);
            fprintf(file, ".L%d:\n", label_next);
            write_asm_bool(file, node->firstChild->nextSibling, label_true, label_false);
            break;
        }

        case T_OR: {
            int label_next = newlabel();
            write_asm_bool(file, node->firstChild, label_true, label_next);
            fprintf(file, ".L%d:\n", label_next);
            write_asm_bool(file, node->firstChild->nextSibling, label_true, label_false);
            break;
        }
        default:
            write_asm_expr(file, node);
            fprintf(file, "\tpop rax\n");
            fprintf(file, "\tcmp rax, 0\n");

            fprintf(file, "\tjne .L%d\n", label_true);
            fprintf(file, "\tjmp .L%d\n", label_false);
            break;
    }
}

static void write_asm_instr(FILE * file, Node * node){
    /*
    oui oui oui je sais je suis très vilain vu que nasmoutput 
    est le fichier de sortie je pourrais enlever l'argument file
    mais je vais surement mettre ces fonctions dans un module
     dédié ou j'aurai peut être pas le nasmoutput
    */
    if (!node) return;

    switch (node->label) {
        case T_IF: {
            int label_true = newlabel();
            int label_false = newlabel();
            write_asm_bool(file, node->firstChild, label_true, label_false);
            fprintf(file, ".L%d:\n", label_true);
            write_asm_instr(file, node->firstChild->nextSibling);
            if (node->firstChild->nextSibling->nextSibling != NULL) {
                int label_fin = newlabel();
                fprintf(file, "\tjmp .L%d\n", label_fin);
                fprintf(file, ".L%d:\n", label_false);
                write_asm_instr(file, node->firstChild->nextSibling->nextSibling);
                fprintf(file, ".L%d:\n", label_fin);
            } 
            else {
                fprintf(file, ".L%d:\n", label_false);
            }
            break;
        }
        case T_WHILE: {
            int label_debut = newlabel();
            int label_corps = newlabel();
            int label_fin = newlabel();
            fprintf(file, ".L%d:\n", label_debut);
            write_asm_bool(file, node->firstChild, label_corps, label_fin);
            fprintf(file, ".L%d:\n", label_corps);
            write_asm_instr(file, node->firstChild->nextSibling);
            fprintf(file, "\tjmp .L%d\n", label_debut); 
            fprintf(file, ".L%d:\n", label_fin);
            break;
        }
        case T_ASSIGN: {
            write_asm_expr(file, node->firstChild->nextSibling);
            Node *var_node = node->firstChild;
            if (var_node->label == T_IDENT) {
                fprintf(file, "\tpop rax\n");

                Symbol *s_local = search_value(var_node->ident, local_table);
                if (s_local != NULL) {
                    fprintf(file, "\tmov [rbp%+d], rax\n", s_local->deplct);
                } 
                else {

                    Symbol *s_global = search_value(var_node->ident, global_table);
                    if (s_global != NULL) {
                        fprintf(file, "\tmov [%s], rax\n", s_global->ident);
                    }
                }
            }
            break;
        }
        case T_FCALL:

            write_asm_expr(file, node);

            fprintf(file, "\tpop rax\n"); 
            break;
        case T_RETURN:
            if (node->firstChild != NULL) {
                write_asm_expr(file, node->firstChild);
                fprintf(file, "\tpop rax\n");
            }
            fprintf(file, "\tmov rsp, rbp\n");
            fprintf(file, "\tpop rbp\n");
            fprintf(file, "\tret\n");
            break;
        default:
            for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
                write_asm_instr(file, child);
            }
            break;
    }
}

//une fonction qui prend un noeud et qui détermine son type
static Type infer_node_type(Node * node){
    switch(node->label){
        case T_NUM:
        return TYPE_INT;
        case T_CHARACTER:
        return TYPE_CHAR;
        case T_IDENT:
        Symbol * s_ident = search_value(node->ident, local_table);
        if (!s_ident)
            s_ident = search_value(node->ident, global_table);
        if (!s_ident)
            return TYPE_INT;
        return s_ident->type;
        break;
        default:
        return TYPE_INT;
        break;
    }
}


void sem(Node *node) {
    
    if (!node) return;
    
    //décommenter cette ligne pour afficher le parcours de l'arbre
    printf("current node : %s\n", StringFromLabel_suppr_juste_pour_print[node->label]);
    
    

    switch (node->label) {
        case T_PROG:
            init_table(&global_table);
            fprintf(nasm_output, "section .text\nglobal _start\n_start:\n");
            fprintf(nasm_output, "\tcall main\n");
            fprintf(nasm_output, "\tmov rdi, rax\n");
            fprintf(nasm_output, "\tmov rax, 60\n");
            fprintf(nasm_output, "\tsyscall\n\n");
            break;

        case T_FUNC:
            /*
            a T_FUNC has two children : 
                firstChild : HEADER
                firstChild->nextSibling : BODY

            the HEADER node contains the header of a function, 
            so its name and its return type
            here we check the name of the function contained
            in node->firstChild->firstChild->nextSibling->ident
            if the name of the function is main, we write the basic asm instructions
            */
            init_table(&local_table);
            current_offset = -8; 
            char *func_name = node->firstChild->firstChild->nextSibling->ident;

            fprintf(nasm_output, "%s:\n", func_name);
            fprintf(nasm_output, "\tpush rbp\n");
            fprintf(nasm_output, "\tmov rbp, rsp\n");
            sem(node->firstChild);
            sem(node->firstChild->nextSibling);
            if (current_offset < 0) {
                fprintf(nasm_output, "\tsub rsp, %d\n", -current_offset);
            }
            Node *param_list = node->firstChild->firstChild->nextSibling->nextSibling; 
            if (param_list != NULL && param_list->label == T_LIST) {
                const char* regs[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
                int param_idx = 0;
                for (Node *p = param_list->firstChild; p != NULL; p = p->nextSibling) {
                    fprintf(nasm_output, "\tmov [rbp-%d], %s\n", (param_idx + 1) * 8, regs[param_idx]);
                    param_idx++;
                }
            }

            write_asm_instr(nasm_output, node->firstChild->nextSibling);
            fprintf(nasm_output, "\tmov rsp, rbp\n");
            fprintf(nasm_output, "\tpop rbp\n");
            fprintf(nasm_output, "\tret\n\n");
        case T_DECL_VARS: 
        {
            Node *list1 = node->firstChild;
            if (list1 == NULL || list1->label != T_LIST) break;

            Node *type_node = list1->firstChild;
            if (type_node == NULL || (type_node->label != T_TYPE && type_node->label != T_TYPE_STRUCT)) break;

            Type current_type = TYPE_INT;
            if (type_node->label == T_TYPE && strcmp(type_node->ident, "char") == 0) 
                current_type = TYPE_CHAR;
            
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
                Type param_type = TYPE_INT;
                if (type_node != NULL && type_node->label == T_TYPE && strcmp(type_node->ident, "char") == 0) {
                    param_type = TYPE_CHAR;
                }
                insert_value(var_node->ident, param_type, current_offset, local_table);
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
        case T_HEADER:
            
            break;
        case T_ASSIGN:

            //fprintf(stderr, "assigning %s to %s (%s <-- %s)\n", node->firstChild->ident, node->firstChild->nextSibling->ident, node->firstChild->ident, node->firstChild->nextSibling->ident);    

            sem(node->firstChild);
            sem(node->firstChild->nextSibling);    

            if (infer_node_type(node->firstChild) == TYPE_CHAR && infer_node_type(node->firstChild->nextSibling) == TYPE_INT) {
                fprintf(stderr, "Avertissement sémantique : affectation d'une expression 'int' à une variable 'char' (ligne %d)\n", node->lineno);
            }

            //write_asm_expr(nasm_output, node);
            break;
        default:
            break;
    }

    if (node->label != T_DECL_VARS && node->label != T_PARAM && node->label != T_HEADER 
        && node->label != T_MEMBER_ACCESS && node->label != T_FCALL 
        && node->label != T_STRUCT_DECL && node->label != T_FUNC
        && node->label != T_ASSIGN) {
        /*
        ce bloc d'instruction permet de parcourir l'arbre dans le cas ou l'on a pas 
        défini de comportement spécifique à un noeud
        il permet de parcourir les enfants d'un noeud anyway
        */
        for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
            sem(child);
        }
    }

    if (node->label == T_HEADER) {
        //printf("name of func : %s\n", node->firstChild->nextSibling->ident);
        
        //i had the detection of main here before, i moved it to T_FUNC
        for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
            if (child->label != T_IDENT && child->label != T_TYPE) {
                sem(child);
            }
        }
    }
    

    if (node->label == T_FUNC) {
        free_table(local_table); 
        local_table = NULL;
    }

    if (node->label == T_PROG) {
        write_asm_global_variables(global_table, nasm_output);
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