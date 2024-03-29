// Compiler of IFJ22 language
// Faculty of Information Technology Brno University of Technology
// Authors:
// Tereza Kubincová (xkubin27)
// Jan Kalenda (xkalen07)

/// \file symtable.c
#include "symtable.h"
#include "error.h"
#include <stdint.h>

/// \brief Hash function
/// \param str Hashed string
/// \return Hash value
size_t htab_hash_function(htab_key_t str) {
    uint32_t h = 0;

    for(const unsigned char *p = (const unsigned char*)str; *p != '\0'; p++)
        h = 65599 * h + *p;
        
    return h;
}

/// \brief Clears the table
/// \param t Hash table
void htab_clear(htab_t * restrict t) {
    // iterate over all table elements and remove them
    for (size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *head = t->arr_ptr[i];
        while (head != NULL) {
            t->arr_ptr[i] = head->next;
            if (head->item.type == H_CONSTANT && head->item.value_type == D_STRING && head->item.value.string[0] != '\0') {
                free(head->item.identifier);
                free(head->item.value.string);
                free(head->item.params);
                free(head->item.params_strict);
                free(head->item.param_names);
                free(head);
                head = t->arr_ptr[i];
                continue;
            } else {
                /* inbuilt functions don't keep track of param names */
                if (head->item.param_names != NULL) {
                    for (int j = 0; j < head->item.param_count; j++) {
                        free(head->item.param_names[j]);
                    }
                }
                free(head->item.identifier);
                free(head->item.params);
                free(head->item.params_strict);             
                free(head->item.param_names);
                free(head);
                head = t->arr_ptr[i];
                continue;
            }
        }
    }
    t->size = 0;
}

/// \brief Finds an item in the table
/// \param t Hash table
/// \param identifier Identifier to be found
/// \return Pointer to the item or NULL if not found
htab_data_t * htab_find(const htab_t * restrict t, htab_key_t identifier) {
    size_t hash = htab_hash_function(identifier) % t->arr_size;

    // iterate over all table elements
    htab_item_t *head = t->arr_ptr[hash];
    while (head != NULL) {
        if (strcmp(head->item.identifier, identifier) == 0) {
            // the identifier was found
            return &head->item;
        }
        head = head->next;
    }
    // identifier not found
    return NULL;
}

/// \brief Executes a function on each item in the table
/// \param t Hash table
/// \param f Function to be executed
void htab_for_each(const htab_t * t, void (*f)(htab_data_t *data)) {
    // iterate over all table items
    for (size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *head = t->arr_ptr[i];
        while (head != NULL) {
            // apply given function
            f(&head->item);
            head = head->next;
        }
    }
}

/// \brief Clears the table and frees the memory
/// \param t Hash table
void htab_free(htab_t * restrict t) {
    // remove all items and free all dynamic memory
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}

/// \brief Initializes the table
/// \param n Size of the table
htab_t *htab_init(size_t n) {
    // dynamically allocate the hash table
    htab_t *tab = malloc(sizeof(htab_t));
    if (tab == NULL) {
        exit(INTERNAL_ERROR);
    }

    // dynamically allocate the hash table's array
    tab->arr_ptr = malloc(n * sizeof(htab_item_t *));
    if (tab->arr_ptr == NULL) {
        free(tab);
        exit(INTERNAL_ERROR);
    }
    tab->arr_size = n;
    tab->size = 0;

    // initialize all array items to NULL
    for (size_t i = 0; i < n; i++) {
        tab->arr_ptr[i] = NULL;
    }
    return tab;
}

/// \brief Inserts an item into the table
/// \param t Hash table
/// \param token Token structure
/// \param key Identifier for hash table
/// \return Pointer to the item or NULL if not found
htab_data_t * htab_insert(htab_t * restrict t, const Token * restrict token, char* key) {
    // check if the identifier exists in the table
    if (token != NULL && (token->type == T_VAR || token->type == T_IDENTIFIER)) {
        htab_data_t *tmp = htab_find(t, key);
        if (tmp != NULL) {
            return tmp;
        }
    }
        
    //  dynamically allocate a new node
    htab_item_t *new = malloc(sizeof(htab_item_t));
    if (new == NULL) {
        exit(INTERNAL_ERROR);
    }

    // initialize the new node
    new->item.identifier = key;
    new->item.params = NULL;
    new->item.params_strict = NULL;
    new->item.param_names = NULL;
    new->item.param_count = 0;
    new->next = NULL;
    
    if (token == NULL) {
        new->item.type = H_CONSTANT;
    } else {
        switch(token->type) {
            case T_IDENTIFIER:
                new->item.type = H_FUNC_ID;
                break;
            case T_VAR:
                new->item.type = H_VAR;
                break;
            case T_INT:
            case T_STRING:
            case T_FLOAT:
                new->item.type = H_CONSTANT;
                break;
            default:
                exit(SYNTAX_ERROR);
        }
    }

    // insert into the table
    size_t hash = htab_hash_function(key) % t->arr_size;
    new->next = t->arr_ptr[hash];
    t->arr_ptr[hash] = new;

    t->size++;
    return &new->item;
}
