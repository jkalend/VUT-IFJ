// htab.h -- rozhraní knihovny htab (řešení IJC-DU2)
// Licence: žádná (Public domain)

// následující řádky zabrání násobnému vložení:
#ifndef __HTAB_H__
#define __HTAB_H__

#include <string.h>     // size_t
#include <stdbool.h>    // bool
#include <stdlib.h>
#include <stdio.h>
#include "scanner.h"

#define AVG_LEN_MAX 15
#define AVG_LEN_MIN 2

typedef const char * htab_key_t; 

// float > int

// Typy:
typedef enum {
    H_CONSTANT,
    H_FUNC_ID,
    H_VAR
} HtabItemType;

typedef enum {
    D_NONE,
    D_INT,
    D_STRING,
    D_FLOAT,
    D_VOID,
    D_BOOL
} DataType;

// Dvojice dat v tabulce:
typedef struct htab_pair {
    HtabItemType type;
    htab_key_t identifier;
    Value value;
    DataType value_type;
    int param_count;
    DataType *params;
    DataType return_type;
} htab_pair_t;                  // typedef podle zadání

// Tabulka:
typedef struct htab_item {
    htab_pair_t item;
    struct htab_item *next;
} htab_item_t;

typedef struct htab {
    size_t size;
    size_t arr_size;
    htab_item_t **arr_ptr;   
} htab_t;


// Rozptylovací (hash) funkce (stejná pro všechny tabulky v programu)
// Pokud si v programu definujete stejnou funkci, použije se ta vaše.
size_t htab_hash_function(htab_key_t str);

// Funkce pro práci s tabulkou:
htab_t *htab_init(size_t n);                    // konstruktor tabulky
size_t htab_size(const htab_t * t);             // počet záznamů v tabulce
size_t htab_bucket_count(const htab_t * t);     // velikost pole
                                                // (umožňuje rezervaci místa)

htab_pair_t * htab_find(htab_t * t, htab_key_t key);  // hledání
htab_pair_t * htab_insert(htab_t * t, Token *token, char *key);

bool htab_erase(htab_t * t, htab_key_t key);    // ruší zadaný záznam

// for_each: projde všechny záznamy a zavolá na ně funkci f
// Pozor: f nesmí měnit klíč .key ani přidávat/rušit položky
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data));

void htab_clear(htab_t * t);    // ruší všechny záznamy
void htab_free(htab_t * t);     // destruktor tabulky

#endif // __HTAB_H__
