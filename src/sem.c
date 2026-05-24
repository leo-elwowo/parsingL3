#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "symb.h"
#include "sem.h"
#include "struct_info.h"

HashTable *global_table = NULL;
HashTable *local_table = NULL;
HashTable *function_table = NULL;
HashTable *struct_table = NULL;
int current_offset = 0; 
extern int printsymb;
extern FILE * nasm_output;


int nberror_sem = 0; //cette variable sera extern dans le .y, elle me permet d'avoir un bon code de retour

static const char *get_func_ret_struct(const char *fn);

/* Returns the struct type name if n evaluates to a struct, NULL otherwise */
static const char *get_node_struct_type(Node *n) {
    if (!n) return NULL;
    if (n->label == T_IDENT) return get_var_struct_type(n->ident);
    if (n->label == T_MEMBER_ACCESS) {
        Node *b = n->firstChild;
        Node *f = b ? b->nextSibling : NULL;
        if (!b || !f) return NULL;
        const char *btype = get_node_struct_type(b);
        if (!btype) return NULL;
        return get_field_struct_type(btype, f->ident);
    }
    if (n->label == T_FCALL && n->firstChild)
        return get_func_ret_struct(n->firstChild->ident);
    return NULL;
}

static int is_node_struct(Node *n) {
    return get_node_struct_type(n) != NULL;
}

/* Resolves a member-access chain to a base symbol and flat slot offset.
   Returns the flat slot offset, or -1 on error.
   *base_sym is set to the root variable's Symbol.
   *is_global is set to 1 if it's a global variable. */
static int get_member_flat_slot(Node *node, Symbol **base_sym, int *is_global) {
    if (node->label == T_IDENT) {
        Symbol *s = search_value(node->ident, local_table);
        if (s) { *base_sym = s; *is_global = 0; return 0; }
        s = search_value(node->ident, global_table);
        if (s) { *base_sym = s; *is_global = 1; return 0; }
        return -1;
    }
    if (node->label != T_MEMBER_ACCESS) return -1;
    Node *base = node->firstChild;
    Node *field = base ? base->nextSibling : NULL;
    if (!base || !field) return -1;
    int base_slot = get_member_flat_slot(base, base_sym, is_global);
    if (base_slot < 0) return -1;
    const char *base_stype = get_node_struct_type(base);
    if (!base_stype) return -1;
    int fidx = find_field_index(base_stype, field->ident);
    if (fidx < 0) return -1;
    return base_slot + fidx;
}

static int newlabel(){
    static int i = 0;
    return ++i;
}

static void write_builtin_io(FILE *file) {
    /*
    a chaque début de programme on écrit la stdio maison
    */
    fprintf(file,
        "; --- fonctions d'E/S built-in ---\n"
        "putchar:\n"
        "\tpush rbp\n\tmov rbp, rsp\n"
        "\tpush rdi\n"
        "\tmov rax, 1\n\tmov rdi, 1\n\tmov rsi, rsp\n\tmov rdx, 1\n\tsyscall\n"
        "\tpop rdi\n"
        "\tmov rsp, rbp\n\tpop rbp\n\tret\n\n"

        "getchar:\n"
        "\tpush rbp\n\tmov rbp, rsp\n"
        "\tsub rsp, 8\n"
        "\tmov rax, 0\n\tmov rdi, 0\n\tmov rsi, rsp\n\tmov rdx, 1\n\tsyscall\n"
        "\txor rax, rax\n"
        "\tmov al, byte [rsp]\n"
        "\tmov rsp, rbp\n\tpop rbp\n\tret\n\n"

        "putint:\n"
        "\tpush rbp\n\tmov rbp, rsp\n"
        "\tsub rsp, 32\n"
        "\tmov rax, rdi\n"
        "\tmov rsi, rsp\n\tadd rsi, 30\n"
        "\tmov byte [rsp+31], 10\n"
        "\txor rcx, rcx\n"
        "\tcmp rax, 0\n\tjge .putint_pos\n"
        "\tneg rax\n"
        ".putint_pos:\n"
        "\tmov r10, 10\n"
        ".putint_loop:\n"
        "\txor rdx, rdx\n\tidiv r10\n"
        "\tadd rdx, '0'\n"
        "\tmov byte [rsi], dl\n\tdec rsi\n\tinc rcx\n"
        "\tcmp rax, 0\n\tjne .putint_loop\n"
        "\tcmp rdi, 0\n\tjge .putint_write\n"
        "\tmov byte [rsi], '-'\n\tdec rsi\n\tinc rcx\n"
        ".putint_write:\n"
        "\tinc rsi\n"
        "\tadd rcx, 1\n"
        "\tmov rax, 1\n\tmov rdi, 1\n\tmov rdx, rcx\n\tsyscall\n"
        "\tmov rsp, rbp\n\tpop rbp\n\tret\n\n"

        "getint:\n"
        "\tpush rbp\n\tmov rbp, rsp\n"
        "\tpush r12\n"
        "\tpush r13\n"
        "\tpush r14\n"
        "\tsub rsp, 8\n"
        "\txor r12, r12\n"
        "\txor r13, r13\n"
        "\txor r14, r14\n"
        "\tmov rax, 0\n\tmov rdi, 0\n\tmov rsi, rsp\n\tmov rdx, 1\n\tsyscall\n"
        "\txor r10, r10\n\tmov r10b, byte [rsp]\n"
        "\tcmp r10, '-'\n\tje .getint_minus\n"
        "\tcmp r10, '+'\n\tje .getint_next\n"
        "\tjmp .getint_check_digit\n"
        ".getint_minus:\n\tmov r13, 1\n\tjmp .getint_next\n"
        ".getint_check_digit:\n"
        "\tcmp r10, '0'\n\tjl .getint_error\n"
        "\tcmp r10, '9'\n\tjg .getint_error\n"
        "\tsub r10, '0'\n"
        "\tmov rax, 10\n\timul r12, rax\n"
        "\tadd r12, r10\n"
        "\tinc r14\n"
        ".getint_next:\n"
        "\tmov rax, 0\n\tmov rdi, 0\n\tmov rsi, rsp\n\tmov rdx, 1\n\tsyscall\n"
        "\txor r10, r10\n\tmov r10b, byte [rsp]\n"
        "\tcmp r10, 10\n\tje .getint_done\n"
        "\tcmp r10, '0'\n\tjl .getint_error\n"
        "\tcmp r10, '9'\n\tjg .getint_error\n"
        "\tsub r10, '0'\n"
        "\tmov rax, 10\n\timul r12, rax\n"
        "\tadd r12, r10\n"
        "\tinc r14\n"
        "\tjmp .getint_next\n"
        ".getint_done:\n"
        "\tcmp r14, 0\n\tje .getint_error\n"
        "\tmov rax, r12\n"
        "\tcmp r13, 0\n\tje .getint_ret\n"
        "\tneg rax\n"
        ".getint_ret:\n"
        "\tadd rsp, 8\n"
        "\tpop r14\n\tpop r13\n\tpop r12\n"
        "\tpop rbp\n\tret\n"
        ".getint_error:\n"
        "\tmov rax, 60\n\tmov rdi, 5\n\tsyscall\n\n"
    );
}
static void write_asm_bool(FILE *file, Node *node, int label_true, int label_false);
//parce que sinon write_asm_expr ne la trouvera pas

static int current_func_is_void = 0;
static int current_func_returns_struct = 0;
static char current_func_return_struct_type[64] = "";
static VarType *var_types_at_func_start = NULL;

typedef struct FuncRetType { char fname[64]; char stype[64]; struct FuncRetType *next; } FuncRetType;
static FuncRetType *func_ret_types = NULL;
static void register_func_ret_struct(const char *fn, const char *st) {
    FuncRetType *e = malloc(sizeof(FuncRetType));
    strncpy(e->fname, fn, 63); e->fname[63] = '\0';
    strncpy(e->stype, st, 63); e->stype[63] = '\0';
    e->next = func_ret_types; func_ret_types = e;
}
static const char *get_func_ret_struct(const char *fn) {
    for (FuncRetType *e = func_ret_types; e; e = e->next)
        if (strcmp(e->fname, fn) == 0) return e->stype;
    return NULL;
}

static void check_expr_for_void_fcall(Node *node) {
    if (!node) return;
    if (node->label == T_FCALL && node->firstChild) {
        Symbol *fs = search_value(node->firstChild->ident, function_table);
        if (fs && fs->deplct % 2 == 1) {
            nberror_sem++;
            fprintf(stderr, "Erreur sémantique : '%s' est void et ne peut pas être utilisé comme expression (ligne %d)\n",
                    node->firstChild->ident, node->lineno);
        }
        return;
    }
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling)
        check_expr_for_void_fcall(child);
}

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


            write_asm_bool(file, node, label_true, label_false);


            fprintf(file, ".L%d:\n", label_true);
            fprintf(file, "\tpush 1\n");
            fprintf(file, "\tjmp .L%d\n", label_fin);


            fprintf(file, ".L%d:\n", label_false);
            fprintf(file, "\tpush 0\n");

            fprintf(file, ".L%d:\n", label_fin);
            break;
        }
        case T_NUM:
        fprintf(file, "\t;mise sur la pile du nombre '%d'\n", node->num);
        fprintf(file, "\tpush %d\n", node->num);
        break;
        case T_CHARACTER:
        fprintf(file, "\t;mise sur la pile du caractère '%d'\n", node->character);
        fprintf(file, "\tpush %d\n", node->character);
        break;
        case T_ADDSUB:
        if (node->firstChild->nextSibling == NULL) {
            // unaire : -x ou +x
            write_asm_expr(file, node->firstChild);
            if (node->byte == '-') {
                fprintf(file, "\tpop rax\n");
                fprintf(file, "\tneg rax\n");   //met en negatif omg
                fprintf(file, "\tpush rax\n");
            }
            break;
        }
        //si c'est une soustraction on fait ca
        //fprintf(file, "\t;on traite la soustraction\n");
        write_asm_expr(file, node->firstChild);    //on va push la partie gauche
        write_asm_expr(file, node->firstChild->nextSibling);    //push la droite
        //et apres on la depile dans r10 et rax
        fprintf(file, "\tpop r10\n");
        fprintf(file, "\tpop rax\n");
        if (node->byte == '-'){
            fprintf(file, "\tsub rax, r10\n");
        }
        else{
            fprintf(file, "\tadd rax, r10\n");
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
        //et apres on la depile dans r10 et rax
        fprintf(file, "\tpop r10\n");
        fprintf(file, "\tpop rax\n");
        if (node->byte == '*'){
            //pour faire imul
            fprintf(file, "\timul rax, r10\n");
            fprintf(file, "\tpush rax\n");    
        }
        else{

            //pour faire idiv, mais je suis pas sur que ce soit la bonne facon
            /*
            update après vérification ca marche mais il faut que le dividende soit positif
            */
            fprintf(file, "\txor rdx, rdx\n");
            fprintf(file, "\tidiv r10\n");
            if (node->byte == '%')
                fprintf(file, "\tpush rdx\n");
            else   
                fprintf(file, "\tpush rax\n");    
        }
        
        break;
        case T_IDENT: {
            Symbol *s_read = search_value(node->ident, local_table);
            if (s_read != NULL) {
                const char *stype_id = get_var_struct_type(node->ident);
                if (stype_id) {
                    int nf = get_struct_num_fields(stype_id);
                    for (int fi = 0; fi < nf; fi++) {
                        fprintf(file, "\tmov rax, [rbp%+d]\n", s_read->deplct - fi * 8);
                        fprintf(file, "\tpush rax\n");
                    }
                } else {
                    fprintf(file, "\tmov rax, [rbp%+d]\n", s_read->deplct);
                    fprintf(file, "\tpush rax\n");
                }
                break;
            }
            s_read = search_value(node->ident, global_table);
            if (s_read != NULL) {
                const char *stype_id = get_var_struct_type(node->ident);
                if (stype_id) {
                    int nf = get_struct_num_fields(stype_id);
                    for (int fi = 0; fi < nf; fi++) {
                        if (fi == 0)
                            fprintf(file, "\tmov rax, [%s]\n", s_read->ident);
                        else
                            fprintf(file, "\tmov rax, [%s + %d]\n", s_read->ident, fi * 8);
                        fprintf(file, "\tpush rax\n");
                    }
                } else {
                    fprintf(file, "\tmov rax, [%s]\n", s_read->ident);
                    fprintf(file, "\tpush rax\n");
                }
            }
            break;
        }
        case T_MEMBER_ACCESS: {
            Symbol *base_sym = NULL; int is_global = 0;
            int flat_slot = get_member_flat_slot(node, &base_sym, &is_global);
            if (flat_slot >= 0 && base_sym) {
                const char *field_stype = get_node_struct_type(node);
                int field_nf = field_stype ? get_struct_num_fields(field_stype) : 1;
                for (int fi = 0; fi < field_nf; fi++) {
                    int slot = flat_slot + fi;
                    if (!is_global) {
                        fprintf(file, "\tmov rax, [rbp%+d]\n", base_sym->deplct - slot * 8);
                    } else {
                        if (slot == 0)
                            fprintf(file, "\tmov rax, [%s]\n", base_sym->ident);
                        else
                            fprintf(file, "\tmov rax, [%s + %d]\n", base_sym->ident, slot * 8);
                    }
                    fprintf(file, "\tpush rax\n");
                }
            }
            break;
        }
        case T_FCALL: {
            char *func_name = node->firstChild->ident;
            Node *args_list = node->firstChild->nextSibling;
            int arg_count = 0;
            if (args_list != NULL && args_list->label == T_LIST) {
                for (Node *arg = args_list->firstChild; arg != NULL; arg = arg->nextSibling) {
                    write_asm_expr(file, arg);
                    /* compter les slots réels (N pour un struct à N champs) */
                    const char *astype = get_node_struct_type(arg);
                    if (astype)
                        arg_count += get_struct_num_fields(astype);
                    else
                        arg_count++;
                }
            }
            const char* regs[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
            for (int i = arg_count - 1; i >= 0; i--) {
                if (i < 6)
                    fprintf(file, "\tpop %s\n", regs[i]);
                else
                    fprintf(file, "\tpop rax\n");  /* discard excess args */
            }
            fprintf(file, "\tcall %s\n", func_name);
            {
                const char *ret_stype = get_func_ret_struct(func_name);
                if (ret_stype) {
                    int nf = get_struct_num_fields(ret_stype);
                    /* push in order: rax (field0), rdx (field1), rcx (field2), ... */
                    const char *ret_regs[] = {"rax", "rdx", "rcx", "r8", "r9"};
                    if (nf > 5) nf = 5;
                    for (int ri = 0; ri < nf; ri++)
                        fprintf(file, "\tpush %s\n", ret_regs[ri]);
                } else {
                    fprintf(file, "\tpush rax\n");
                }
            }
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

            fprintf(file, "\tpop r10\n");
            fprintf(file, "\tpop rax\n");
            fprintf(file, "\tcmp rax, r10\n");
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
            
            fprintf(file, "\tpop r10\n");
            fprintf(file, "\tpop rax\n");
            fprintf(file, "\tcmp rax, r10\n");
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
                const char *lstype = get_var_struct_type(var_node->ident);
                if (lstype) {
                    int nf = get_struct_num_fields(lstype);
                    Symbol *sl = search_value(var_node->ident, local_table);
                    Symbol *sg = sl ? NULL : search_value(var_node->ident, global_table);
                    /* les champs sont empilés dans l'ordre 0..nf-1, on dépile nf-1..0 */
                    for (int fi = nf - 1; fi >= 0; fi--) {
                        fprintf(file, "\tpop rax\n");
                        if (sl)
                            fprintf(file, "\tmov [rbp%+d], rax\n", sl->deplct - fi * 8);
                        else if (sg) {
                            if (fi == 0)
                                fprintf(file, "\tmov [%s], rax\n", sg->ident);
                            else
                                fprintf(file, "\tmov [%s + %d], rax\n", sg->ident, fi * 8);
                        }
                    }
                } else {
                    fprintf(file, "\tpop rax\n");
                    Symbol *s_local = search_value(var_node->ident, local_table);
                    if (s_local != NULL) {
                        fprintf(file, "\tmov [rbp%+d], rax\n", s_local->deplct);
                    } else {
                        Symbol *s_global = search_value(var_node->ident, global_table);
                        if (s_global != NULL) {
                            fprintf(file, "\tmov [%s], rax\n", s_global->ident);
                        }
                    }
                }
            } else if (var_node->label == T_MEMBER_ACCESS) {
                Symbol *base_sym = NULL; int is_global = 0;
                int flat_slot = get_member_flat_slot(var_node, &base_sym, &is_global);
                if (flat_slot >= 0 && base_sym) {
                    const char *field_stype = get_node_struct_type(var_node);
                    int field_nf = field_stype ? get_struct_num_fields(field_stype) : 1;
                    for (int fi = field_nf - 1; fi >= 0; fi--) {
                        fprintf(file, "\tpop rax\n");
                        int slot = flat_slot + fi;
                        if (!is_global) {
                            fprintf(file, "\tmov [rbp%+d], rax\n", base_sym->deplct - slot * 8);
                        } else {
                            if (slot == 0)
                                fprintf(file, "\tmov [%s], rax\n", base_sym->ident);
                            else
                                fprintf(file, "\tmov [%s + %d], rax\n", base_sym->ident, slot * 8);
                        }
                    }
                }
            }
            break;
        }
        case T_FCALL: {
            write_asm_expr(file, node);
            const char *fcall_fname = node->firstChild ? node->firstChild->ident : NULL;
            const char *fcall_ret_stype = fcall_fname ? get_func_ret_struct(fcall_fname) : NULL;
            if (fcall_ret_stype) {
                int nf = get_struct_num_fields(fcall_ret_stype);
                for (int fi = 0; fi < nf; fi++) fprintf(file, "\tpop rax\n");
            } else {
                fprintf(file, "\tpop rax\n");
            }
            break;
        }
        case T_RETURN:
            if (node->firstChild != NULL) {
                write_asm_expr(file, node->firstChild);
                if (current_func_returns_struct && current_func_return_struct_type[0]) {
                    int nf = get_struct_num_fields(current_func_return_struct_type);
                    /* stack: field0 ... field(nf-1)  ← top */
                    /* ret regs: rax=field0, rdx=field1, rcx=field2, r8=field3, r9=field4 */
                    const char *ret_regs[] = {"rax", "rdx", "rcx", "r8", "r9"};
                    if (nf > 5) nf = 5;
                    for (int ri = nf - 1; ri >= 0; ri--)
                        fprintf(file, "\tpop %s\n", ret_regs[ri]);
                } else {
                    fprintf(file, "\tpop rax\n");
                }
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
        case T_IDENT: {
            Symbol *s_ident = search_value(node->ident, local_table);
            if (!s_ident)
                s_ident = search_value(node->ident, global_table);
            if (!s_ident)
                return TYPE_INT;
            return s_ident->type;
        }
        default:
        return TYPE_INT;
        break;
    }
}


void sem(Node *node) {
    
    if (!node) return;
    
    //décommenter cette ligne pour afficher le parcours de l'arbre
    //printf("current node : %s\n", StringFromLabel_suppr_juste_pour_print[node->label]);
    
    

    switch (node->label) {
        case T_PROG:
            init_table(&global_table);
            init_table(&function_table);
            init_table(&struct_table);

            /* deplct = param_count * 2 + is_void */
            insert_value("putchar", TYPE_INT, 3, function_table); /* 1 param, void */
            insert_value("getchar", TYPE_INT, 0, function_table); /* 0 params, non-void */
            insert_value("putint",  TYPE_INT, 3, function_table); /* 1 param, void */
            insert_value("getint",  TYPE_INT, 0, function_table); /* 0 params, non-void */

            {
                Node *first = node->firstChild;
                Node *decl_foncts = NULL;

                if (first != NULL && first->label == T_LIST) {
                    decl_foncts = first->nextSibling;
                } else if (first != NULL && first->label == T_DECL_FONCTS) {
                    decl_foncts = first;
                }

                if (decl_foncts != NULL) {
                    for (Node *fn = decl_foncts->firstChild; fn != NULL; fn = fn->nextSibling) {
                        Node *name_node = fn->firstChild->firstChild->nextSibling;
                        if (search_value(name_node->ident, function_table) != NULL) {
                            nberror_sem++;
                            fprintf(stderr, "Erreur sémantique : fonction '%s' déjà déclarée\n", name_node->ident);
                        } else {
                            Node *ret_type = fn->firstChild->firstChild;
                            int returns_int = (ret_type != NULL && ret_type->label == T_TYPE
                                               && strcmp(ret_type->ident, "int") == 0);
                            int is_void = (ret_type != NULL && ret_type->label == T_TYPE
                                           && strcmp(ret_type->ident, "void") == 0);
                            int param_count = 0;
                            Node *plist = fn->firstChild->firstChild->nextSibling->nextSibling;
                            if (plist != NULL && plist->label == T_LIST)
                                for (Node *p = plist->firstChild; p; p = p->nextSibling)
                                    if (p->label == T_PARAM) param_count++;
                            if (strcmp(name_node->ident, "main") == 0) {
                                if (!returns_int) {
                                    nberror_sem++;
                                    fprintf(stderr, "Erreur sémantique : 'main' doit retourner int\n");
                                }
                                if (param_count > 0) {
                                    nberror_sem++;
                                    fprintf(stderr, "Erreur sémantique : 'main' ne doit prendre aucun argument\n");
                                }
                            }
                            insert_value(name_node->ident, TYPE_INT, param_count * 2 + is_void, function_table);
                        }
                    }
                }
                if (search_value("main", function_table) == NULL) {
                    nberror_sem++;
                    fprintf(stderr, "Erreur sémantique : fonction 'main' manquante\n");
                }
            }

            fprintf(nasm_output, "DEFAULT REL\nsection .text\nglobal _start\n_start:\n");
            fprintf(nasm_output, "\tcall main\n");
            fprintf(nasm_output, "\tmov rdi, rax\n");
            fprintf(nasm_output, "\tmov rax, 60\n");
            fprintf(nasm_output, "\tsyscall\n\n");
            write_builtin_io(nasm_output);
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
            {
                Symbol *fsi = search_value(func_name, function_table);
                current_func_is_void = (fsi != NULL && fsi->deplct % 2 == 1);
                Node *ret_type = node->firstChild->firstChild;
                current_func_returns_struct = (ret_type != NULL && ret_type->label == T_TYPE_STRUCT);
                current_func_return_struct_type[0] = '\0';
                if (current_func_returns_struct && ret_type->firstChild) {
                    strncpy(current_func_return_struct_type, ret_type->firstChild->ident, 63);
                    register_func_ret_struct(func_name, ret_type->firstChild->ident);
                }
                var_types_at_func_start = var_types;
            }

            fprintf(nasm_output, "%s:\n", func_name);
            fprintf(nasm_output, "\tpush rbp\n");
            fprintf(nasm_output, "\tmov rbp, rsp\n");
            sem(node->firstChild);
            sem(node->firstChild->nextSibling);
            int alloc = -current_offset - 8;  // -8 car current_offset part de -8
            if (alloc > 0) {
                fprintf(nasm_output, "\tsub rsp, %d\n", alloc);
            }
            Node *param_list = node->firstChild->firstChild->nextSibling->nextSibling;
            if (param_list != NULL && param_list->label == T_LIST) {
                const char* regs[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
                int param_idx = 0;
                for (Node *p = param_list->firstChild; p != NULL; p = p->nextSibling) {
                    Node *ptype = p->firstChild;
                    int nf = 1;
                    if (ptype && ptype->label == T_TYPE_STRUCT && ptype->firstChild) {
                        int n = get_struct_num_fields(ptype->firstChild->ident);
                        if (n > 0) nf = n;
                    }
                    for (int fi = 0; fi < nf && param_idx < 6; fi++) {
                        fprintf(nasm_output, "\tmov [rbp-%d], %s\n", (param_idx + 1) * 8, regs[param_idx]);
                        param_idx++;
                    }
                }
            }

            write_asm_instr(nasm_output, node->firstChild->nextSibling);
            fprintf(nasm_output, "\tmov rsp, rbp\n");
            fprintf(nasm_output, "\tpop rbp\n");
            fprintf(nasm_output, "\tret\n\n");
            break;
        case T_DECL_VARS: 
        {
            Node *list1 = node->firstChild;
            if (list1 == NULL || list1->label != T_LIST) break;

            Node *type_node = list1->firstChild;
            if (type_node == NULL || (type_node->label != T_TYPE && type_node->label != T_TYPE_STRUCT)) break;

            if (type_node->label == T_TYPE_STRUCT) {
                Node *sname = type_node->firstChild;
                if (sname != NULL && search_value(sname->ident, struct_table) == NULL) {
                    nberror_sem++;
                    fprintf(stderr, "Erreur sémantique : type 'struct %s' non déclaré (ligne %d)\n",
                            sname->ident, type_node->lineno);
                }
            }

            Type current_type = TYPE_INT;
            if (type_node->label == T_TYPE && strcmp(type_node->ident, "char") == 0)
                current_type = TYPE_CHAR;
            
            HashTable *target_table = (local_table != NULL) ? local_table : global_table;


            int slot_size = 8;
            const char *struct_type_name = NULL;
            if (type_node->label == T_TYPE_STRUCT && type_node->firstChild != NULL) {
                struct_type_name = type_node->firstChild->ident;
                int nf = get_struct_num_fields(struct_type_name);
                if (nf > 1) slot_size = nf * 8;
            }

            Node *list2 = type_node->nextSibling;
            if (list2 != NULL && list2->label == T_LIST) {
                Node *var_node = list2->firstChild;
                while (var_node != NULL) {
                    if (var_node->label == T_IDENT) {
                        int doublon = (search_value(var_node->ident, target_table) != NULL);
                        int conflit_fonc = (target_table == global_table &&
                                            search_value(var_node->ident, function_table) != NULL);
                        if (doublon || conflit_fonc) {
                            nberror_sem++;
                            if (conflit_fonc)
                                fprintf(stderr, "Erreur sémantique : '%s' déjà déclaré comme fonction (ligne %d)\n", var_node->ident, var_node->lineno);
                            else
                                fprintf(stderr, "Erreur sémantique : '%s' déjà déclaré (ligne %d)\n", var_node->ident, var_node->lineno);
                        } else {
                            insert_value(var_node->ident, current_type, current_offset, target_table);
                            if (struct_type_name)
                                register_var_struct_type(var_node->ident, struct_type_name);
                        }
                        current_offset -= slot_size;
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
            if (type_node != NULL && type_node->label == T_TYPE_STRUCT) {
                Node *sname = type_node->firstChild;
                if (sname != NULL && search_value(sname->ident, struct_table) == NULL) {
                    nberror_sem++;
                    fprintf(stderr, "Erreur sémantique : type 'struct %s' non déclaré (ligne %d)\n",
                            sname->ident, type_node->lineno);
                }
            }
            if (var_node != NULL && var_node->label == T_IDENT) {
                Type param_type = TYPE_INT;
                if (type_node != NULL && type_node->label == T_TYPE && strcmp(type_node->ident, "char") == 0) {
                    param_type = TYPE_CHAR;
                }
                if (search_value(var_node->ident, local_table) != NULL) {
                    nberror_sem++;
                    fprintf(stderr, "Erreur sémantique : paramètre '%s' déjà déclaré (ligne %d)\n", var_node->ident, var_node->lineno);
                } else {
                    insert_value(var_node->ident, param_type, current_offset, local_table);
                    if (type_node != NULL && type_node->label == T_TYPE_STRUCT && type_node->firstChild != NULL)
                        register_var_struct_type(var_node->ident, type_node->firstChild->ident);
                }
                if (type_node != NULL && type_node->label == T_TYPE_STRUCT && type_node->firstChild != NULL) {
                    int nf = get_struct_num_fields(type_node->firstChild->ident);
                    current_offset -= (nf > 0 ? nf : 1) * 8;
                } else {
                    current_offset -= 8;
                }
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
                nberror_sem++;
                fprintf(stderr, "Erreur sémantique : variable '%s' non déclarée (ligne %d)\n", node->ident, node->lineno);
            }
            break;
        }

        case T_MEMBER_ACCESS: {
            Node *base  = node->firstChild;
            Node *field = base ? base->nextSibling : NULL;
            if (base) sem(base);
            if (base && field) {
                if (base->label == T_IDENT) {
                    const char *stype = get_var_struct_type(base->ident);
                    if (stype) {
                        if (find_field_index(stype, field->ident) < 0) {
                            nberror_sem++;
                            fprintf(stderr, "Erreur sémantique : '%s' n'est pas un champ de 'struct %s' (ligne %d)\n",
                                    field->ident, stype, node->lineno);
                        }
                    } else {
                        Symbol *s = search_value(base->ident, local_table);
                        if (!s) s = search_value(base->ident, global_table);
                        if (s) {
                            nberror_sem++;
                            fprintf(stderr, "Erreur sémantique : '%s' n'est pas de type struct (ligne %d)\n",
                                    base->ident, node->lineno);
                        }
                    }
                } else if (base->label == T_MEMBER_ACCESS) {
                    const char *btype = get_node_struct_type(base);
                    if (btype) {
                        if (find_field_index(btype, field->ident) < 0) {
                            nberror_sem++;
                            fprintf(stderr, "Erreur sémantique : '%s' n'est pas un champ de 'struct %s' (ligne %d)\n",
                                    field->ident, btype, node->lineno);
                        }
                    } else {
                        nberror_sem++;
                        fprintf(stderr, "Erreur sémantique : accès de champ sur une expression non-struct (ligne %d)\n",
                                node->lineno);
                    }
                }
            }
            break;
        }

        case T_FCALL:
            if (node->firstChild != NULL) {
                Symbol *fcs = search_value(node->firstChild->ident, function_table);
                if (fcs == NULL) {
                    nberror_sem++;
                    fprintf(stderr, "Erreur sémantique : fonction '%s' non déclarée (ligne %d)\n",
                            node->firstChild->ident, node->lineno);
                } else {
                    int expected = fcs->deplct / 2;
                    int actual = 0;
                    Node *anode = node->firstChild->nextSibling;
                    if (anode != NULL && anode->label == T_LIST)
                        for (Node *a = anode->firstChild; a; a = a->nextSibling)
                            actual++;
                    if (actual != expected) {
                        nberror_sem++;
                        fprintf(stderr, "Erreur sémantique : '%s' attend %d argument(s), %d fourni(s) (ligne %d)\n",
                                node->firstChild->ident, expected, actual, node->lineno);
                    }
                }
                if (node->firstChild->nextSibling != NULL) {
                    Node *args = node->firstChild->nextSibling;
                    if (args->label == T_LIST) {
                        for (Node *arg = args->firstChild; arg != NULL; arg = arg->nextSibling) {
                            check_expr_for_void_fcall(arg);
                        }
                    }
                    sem(args);
                }
            }
            break;

        case T_STRUCT_DECL:
            if (node->firstChild != NULL) {
                if (search_value(node->firstChild->ident, struct_table) != NULL) {
                    nberror_sem++;
                    fprintf(stderr, "Erreur sémantique : 'struct %s' déjà déclarée (ligne %d)\n",
                            node->firstChild->ident, node->lineno);
                } else {
                    insert_value(node->firstChild->ident, TYPE_INT, 0, struct_table);
                    Node *fl = node->firstChild->nextSibling;
                    if (fl != NULL) {
                        HashTable *field_check;
                        init_table(&field_check);
                        for (Node *dv = fl->firstChild; dv; dv = dv->nextSibling) {
                            if (dv->label != T_DECL_VARS) continue;
                            Node *inner = dv->firstChild;
                            if (!inner) continue;
                            Node *type_node = inner->firstChild;
                            /* Vérifier que le type de champ struct est déclaré */
                            if (type_node && type_node->label == T_TYPE_STRUCT) {
                                Node *sname = type_node->firstChild;
                                if (sname && search_value(sname->ident, struct_table) == NULL) {
                                    nberror_sem++;
                                    fprintf(stderr, "Erreur sémantique : type 'struct %s' non déclaré (ligne %d)\n",
                                            sname->ident, type_node->lineno);
                                }
                            }
                            Node *names = type_node ? type_node->nextSibling : NULL;
                            if (!names) continue;
                            for (Node *id = names->firstChild; id; id = id->nextSibling) {
                                if (id->label != T_IDENT) continue;
                                if (search_value(id->ident, field_check) != NULL) {
                                    nberror_sem++;
                                    fprintf(stderr, "Erreur sémantique : champ '%s' déclaré plusieurs fois dans 'struct %s' (ligne %d)\n",
                                            id->ident, node->firstChild->ident, id->lineno);
                                } else {
                                    insert_value(id->ident, TYPE_INT, 0, field_check);
                                }
                            }
                        }
                        free_table(field_check);
                    }
                    register_struct_def(node->firstChild->ident, node->firstChild->nextSibling);
                }
            }
            break;
        case T_HEADER: {
            Node *ret_type = node->firstChild;
            if (ret_type != NULL && ret_type->label == T_TYPE_STRUCT) {
                Node *sname = ret_type->firstChild;
                if (sname != NULL && search_value(sname->ident, struct_table) == NULL) {
                    nberror_sem++;
                    fprintf(stderr, "Erreur sémantique : type de retour 'struct %s' non déclaré (ligne %d)\n",
                            sname->ident, ret_type->lineno);
                }
            }
            break;
        }
        case T_RETURN:
            if (node->firstChild) check_expr_for_void_fcall(node->firstChild);
            if (node->firstChild && current_func_is_void) {
                nberror_sem++;
                fprintf(stderr, "Erreur sémantique : return avec valeur dans fonction void (ligne %d)\n", node->lineno);
            } else if (node->firstChild) {
                Node *ret = node->firstChild;
                const char *ret_stype = get_node_struct_type(ret);
                if (ret_stype != NULL && !current_func_returns_struct) {
                    nberror_sem++;
                    fprintf(stderr, "Erreur sémantique : impossible de retourner une struct (ligne %d)\n", node->lineno);
                } else if (ret_stype == NULL && current_func_returns_struct && ret->label != T_FCALL) {
                    nberror_sem++;
                    fprintf(stderr, "Erreur sémantique : retour d'une valeur non-struct dans une fonction retournant une struct (ligne %d)\n", node->lineno);
                }
            }
            break;

        case T_IF:
        case T_WHILE:
            if (node->firstChild) {
                check_expr_for_void_fcall(node->firstChild);
                if (is_node_struct(node->firstChild)) { // <--- VÉRIFICATION ICI
                    nberror_sem++;
                    fprintf(stderr, "Erreur sémantique : condition ne peut pas être une struct (ligne %d)\n", node->lineno);
                }
            }
            break;
        case T_NOT:
        case T_ADDSUB:
        case T_DIVSTAR:
        case T_EQ:
        case T_ORDER:
        case T_AND:
        case T_OR: {
            Node *op_lhs = node->firstChild;
            Node *op_rhs = op_lhs ? op_lhs->nextSibling : NULL;
            if (is_node_struct(op_lhs) || is_node_struct(op_rhs)) {
                nberror_sem++;
                fprintf(stderr, "Erreur sémantique : opération arithmétique/logique interdite sur une struct (ligne %d)\n", node->lineno);
            }
            break;
        }
        case T_ASSIGN:

            //fprintf(stderr, "assigning %s to %s (%s <-- %s)\n", node->firstChild->ident, node->firstChild->nextSibling->ident, node->firstChild->ident, node->firstChild->nextSibling->ident);    

            sem(node->firstChild);
            sem(node->firstChild->nextSibling);

            check_expr_for_void_fcall(node->firstChild->nextSibling);

            if (infer_node_type(node->firstChild) == TYPE_CHAR && infer_node_type(node->firstChild->nextSibling) == TYPE_INT) {
                fprintf(stderr, "Avertissement sémantique : affectation d'une expression 'int' à une variable 'char' (ligne %d)\n", node->lineno);
            }

            {
                /* Vérifier la compatibilité de type struct dans les affectations */
                Node *lhs = node->firstChild;
                Node *rhs = node->firstChild->nextSibling;
                const char *lhs_stype = NULL;
                const char *rhs_stype = NULL;
                /* Déterminer le type struct du LHS */
                if (lhs->label == T_IDENT)
                    lhs_stype = get_var_struct_type(lhs->ident);
                else if (lhs->label == T_MEMBER_ACCESS && lhs->firstChild && lhs->firstChild->label == T_IDENT) {
                    const char *base_stype = get_var_struct_type(lhs->firstChild->ident);
                    if (base_stype && lhs->firstChild->nextSibling)
                        lhs_stype = NULL; /* champ d'un struct = int/char, pas struct (cas simple) */
                }
                /* Déterminer le type struct du RHS */
                if (rhs)
                    rhs_stype = get_node_struct_type(rhs);
                /* Vérifier la compatibilité */
                if (lhs_stype != NULL && rhs_stype == NULL && rhs &&
                    rhs->label != T_FCALL) {
                    nberror_sem++;
                    fprintf(stderr, "Erreur sémantique : affectation d'une expression non-struct à 'struct %s' (ligne %d)\n",
                            lhs_stype, node->lineno);
                } else if (lhs_stype != NULL && rhs_stype != NULL && strcmp(lhs_stype, rhs_stype) != 0) {
                    nberror_sem++;
                    fprintf(stderr, "Erreur sémantique : affectation de 'struct %s' à 'struct %s' incompatible (ligne %d)\n",
                            rhs_stype, lhs_stype, node->lineno);
                } else if (lhs_stype == NULL && rhs_stype != NULL && lhs->label == T_IDENT) {
                    nberror_sem++;
                    fprintf(stderr, "Erreur sémantique : affectation d'une 'struct' à un type de base interdite (ligne %d)\n", node->lineno);
                }
            }

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
            if (child->label != T_IDENT && child->label != T_TYPE && child->label != T_TYPE_STRUCT) {
                sem(child);
            }
        }
    }
    

    if (node->label == T_FUNC) {
        while (var_types != var_types_at_func_start) {
            VarType *tmp = var_types;
            var_types = var_types->next;
            free(tmp);
        }
        free_table(local_table);
        local_table = NULL;
    }

    if (node->label == T_PROG) {
        if (global_table != NULL && global_table->size > 0) {
            fprintf(nasm_output, "section .bss\n");
            for (int i = 0; i < global_table->cap; i++) {
                Bucket tmp = global_table->elt[i];
                while (tmp != NULL) {
                    const char *stype = get_var_struct_type(tmp->val->ident);
                    int nslots = stype ? get_struct_num_fields(stype) : 1;
                    if (nslots < 1) nslots = 1;
                    fprintf(nasm_output, "\t%s: resq %d\n", tmp->val->ident, nslots);
                    tmp = tmp->prochain;
                }
            }
            fprintf(nasm_output, "\n");
        }
        free_table(function_table);
        free_table(struct_table);
        function_table = NULL;
        struct_table = NULL;
        free_struct_info();
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