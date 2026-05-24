#ifndef STRUCT_INFO_H
#define STRUCT_INFO_H

#include "tree.h"

typedef struct FieldDef {
    char name[64];
    int index;
    char struct_type[64]; /* "" if int/char, "TypeName" if struct field */
    struct FieldDef *next;
} FieldDef;

typedef struct StructDef {
    char name[64];
    FieldDef *fields;
    int num_fields;
    struct StructDef *next;
} StructDef;

typedef struct VarType {
    char var_name[64];
    char struct_name[64];
    struct VarType *next;
} VarType;

extern StructDef *struct_defs;
extern VarType   *var_types;

void register_struct_def(const char *struct_name, Node *field_list_node);

StructDef * find_struct_def(const char *name);

int find_field_index(const char *struct_name, const char *field_name);

int get_struct_num_fields(const char *struct_name);

void register_var_struct_type(const char *var_name, const char *struct_name);

const char *get_var_struct_type(const char *var_name);

const char *get_field_struct_type(const char *struct_name, const char *field_name);

void free_struct_info(void);

#endif
