#include <stdlib.h>
#include <string.h>
#include "struct_info.h"
#include "tree.h"

StructDef *struct_defs = NULL;
VarType   *var_types   = NULL;

void register_struct_def(const char *struct_name, Node *field_list_node) {
    if (find_struct_def(struct_name) != NULL)
        return;

    StructDef *sd = malloc(sizeof(StructDef));
    strncpy(sd->name, struct_name, 63); sd->name[63] = '\0';
    sd->fields = NULL;
    sd->num_fields = 0;

    int flat_idx = 0;  /* cumulative flat 8-byte slot index */
    if (field_list_node != NULL) {
        for (Node *dv = field_list_node->firstChild; dv != NULL; dv = dv->nextSibling) {
            if (dv->label != T_DECL_VARS) continue;
            Node *inner = dv->firstChild;
            if (!inner) continue;
            Node *type_node = inner->firstChild;
            Node *decl_list = type_node ? type_node->nextSibling : NULL;
            if (!decl_list) continue;
            char field_stype[64] = "";
            int field_slots = 1;
            if (type_node && type_node->label == T_TYPE_STRUCT && type_node->firstChild) {
                strncpy(field_stype, type_node->firstChild->ident, 63);
                int n = get_struct_num_fields(field_stype);
                if (n > 0) field_slots = n;
            }
            for (Node *id = decl_list->firstChild; id != NULL; id = id->nextSibling) {
                if (id->label != T_IDENT) continue;
                FieldDef *fd = malloc(sizeof(FieldDef));
                strncpy(fd->name, id->ident, 63); fd->name[63] = '\0';
                fd->index = flat_idx;
                strncpy(fd->struct_type, field_stype, 63); fd->struct_type[63] = '\0';
                fd->next = sd->fields;
                sd->fields = fd;
                flat_idx += field_slots;
            }
        }
    }

    FieldDef *prev = NULL, *curr = sd->fields, *nxt;
    while (curr) { nxt = curr->next; curr->next = prev; prev = curr; curr = nxt; }
    sd->fields = prev;

    sd->num_fields = flat_idx;  /* total flat 8-byte slots */
    sd->next = struct_defs;
    struct_defs = sd;
}

StructDef *find_struct_def(const char *name) {
    for (StructDef *sd = struct_defs; sd; sd = sd->next)
        if (strcmp(sd->name, name) == 0) return sd;
    return NULL;
}

int find_field_index(const char *struct_name, const char *field_name) {
    StructDef *sd = find_struct_def(struct_name);
    if (!sd) return -1;
    for (FieldDef *f = sd->fields; f; f = f->next)
        if (strcmp(f->name, field_name) == 0) return f->index;
    return -1;
}

int get_struct_num_fields(const char *struct_name) {
    StructDef *sd = find_struct_def(struct_name);
    return sd ? sd->num_fields : 1;
}

void register_var_struct_type(const char *var_name, const char *struct_name) {
    VarType *vt = malloc(sizeof(VarType));
    strncpy(vt->var_name, var_name, 63);     vt->var_name[63] = '\0';
    strncpy(vt->struct_name, struct_name, 63); vt->struct_name[63] = '\0';
    vt->next = var_types;
    var_types = vt;
}

const char *get_var_struct_type(const char *var_name) {
    for (VarType *vt = var_types; vt; vt = vt->next)
        if (strcmp(vt->var_name, var_name) == 0) return vt->struct_name;
    return NULL;
}

const char *get_field_struct_type(const char *struct_name, const char *field_name) {
    StructDef *sd = find_struct_def(struct_name);
    if (!sd) return NULL;
    for (FieldDef *f = sd->fields; f; f = f->next)
        if (strcmp(f->name, field_name) == 0)
            return f->struct_type[0] ? f->struct_type : NULL;
    return NULL;
}

void free_struct_info(void) {
    StructDef *sd = struct_defs;
    while (sd) {
        FieldDef *f = sd->fields;
        while (f) { FieldDef *nf = f->next; free(f); f = nf; }
        StructDef *nsd = sd->next; free(sd); sd = nsd;
    }
    struct_defs = NULL;

    VarType *vt = var_types;
    while (vt) { VarType *nvt = vt->next; free(vt); vt = nvt; }
    var_types = NULL;
}
