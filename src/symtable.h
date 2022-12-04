// Compiler of IFJ22 language
// Faculty of Information Technology Brno University of Technology
// Authors:
// Tereza Kubincová (xkubin27)
// Jan Kalenda (xkalen07)

#ifndef __HTAB_H__
#define __HTAB_H__

#include <string.h>     // size_t
#include <stdbool.h>    // bool
#include <stdlib.h>
#include <stdio.h>
#include "scanner.h"

typedef char * htab_key_t; 

// Types:
typedef enum {
    H_CONSTANT,
    H_FUNC_ID,
    H_VAR
} HtabItemType;

// Data types:
typedef enum {
    D_NONE,
    D_INT,
    D_STRING,
    D_FLOAT,
    D_VOID,
    D_BOOL,
    D_UNDEF
} DataType;

// Data pair in table:
typedef struct htab_pair {
    bool strict_return;
    int param_count;
    HtabItemType type;
    htab_key_t identifier;
    Value value;
    DataType value_type;
    DataType return_type;
    DataType *params;
    bool *params_strict;
    char **param_names;
} htab_data_t;

// Table item:
typedef struct htab_item {
    htab_data_t item;
    struct htab_item *next;
} htab_item_t;

// Table:
typedef struct htab {
    size_t size;
    size_t arr_size;
    htab_item_t **arr_ptr;   
} htab_t;


// Hash function:
size_t htab_hash_function(htab_key_t str);

htab_t *htab_init(size_t n);

htab_data_t * htab_find(const htab_t * t, htab_key_t key);

htab_data_t * htab_insert(htab_t * t, const Token *token, char *key);

void htab_for_each(const htab_t * t, void (*f)(htab_data_t *data));

void htab_clear(htab_t * t);

void htab_free(htab_t * t);

#endif // __HTAB_H__
