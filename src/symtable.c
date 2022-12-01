#include "symtable.h"

size_t htab_hash_function(htab_key_t str) 
{
    unsigned int h = 0;     // musí mít 32 bitů
    const unsigned char *p;

    for(p = (const unsigned char*)str; *p != '\0'; p++)
        h = 65599 * h + *p;
        
    return h;
}


size_t htab_bucket_count(const htab_t * t)
{
    return t->arr_size;
}

void htab_clear(htab_t * t)
{
    // iterate over all table elements and remove them
    for (size_t i = 0; i < t->arr_size; i++)
    {
        htab_item_t *head = t->arr_ptr[i];
        while (head != NULL)
        {
            t->arr_ptr[i] = head->next;
            free((void *)head->item.identifier);
            free(head);
            head = t->arr_ptr[i];
        }
    }
    t->size = 0;
}

bool htab_erase(htab_t * t, htab_key_t identifier)
{
    size_t hash = htab_hash_function(identifier) % t->arr_size;

    htab_item_t *head = t->arr_ptr[hash];

    if (head == NULL) return false;
    else if (strcmp(head->item.identifier, identifier) == 0)
    {
        t->arr_ptr[hash] = head->next;
        free((void *)head->item.identifier);
        free(head);

        t->size--;
        return true;
    }
    else 
    {
        htab_item_t *delete = NULL;
        while (head->next != NULL)
        {
            if (strcmp(head->next->item.identifier, identifier) == 0)
            {
                delete = head->next;
                head->next = head->next->next;
                free((void *)delete->item.identifier);
                free(delete);

                t->size--;
                return true;
            }
            head = head->next;
        }
    }

    return false;
}

htab_pair_t * htab_find(htab_t * t, htab_key_t identifier)
{
    size_t hash = htab_hash_function(identifier) % t->arr_size;

    // iterate over all table elements
    htab_item_t *head = t->arr_ptr[hash];
    while (head != NULL)
    {
        if (strcmp(head->item.identifier, identifier) == 0)
        {
            // the identifier was found
            return &head->item;
        }
        head = head->next;
    }
    // identifier not found
    return NULL;
}

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data))
{
    // iterate over all table items
    for (size_t i = 0; i < t->arr_size; i++)
    {
        htab_item_t *head = t->arr_ptr[i];
        while (head != NULL)
        {
            // apply given function
            f(&head->item);
            head = head->next;
        }
    }
}


void htab_free(htab_t * t)
{
    // remove all items and free all dynamic memory
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}

htab_t *htab_init(size_t n)
{
    // dynamically allocate the hash table
    htab_t *tab = malloc(sizeof(htab_t));
    if (tab == NULL)
    {
        return NULL;
    }

    // dynamically allocate the hash table's array
    tab->arr_ptr = malloc(n * sizeof(htab_item_t *));
    if (tab->arr_ptr == NULL)
    {
        free(tab);
        return NULL;
    }
    tab->arr_size = n;
    tab->size = 0;

    // initialize all array items to NULL
    for (size_t i = 0; i < n; i++)
    {
        tab->arr_ptr[i] = NULL;
    }
    return tab;
}


htab_pair_t * htab_insert(htab_t * t, Token *token, char* key)
{
    // check if the identifier exists in the table
    if (token != NULL && (token->type == T_VAR || token->type == T_IDENTIFIER)) {
        htab_pair_t *tmp = htab_find(t, key);
        if (tmp != NULL) {
            return tmp;
        }
    }
        
    //  dynamically allocate a new node
    htab_item_t *new = malloc(sizeof(htab_item_t));
    if (new == NULL)
    {
        return NULL;
    }
//    new->item.identifier = malloc((strlen(key) + 1) * sizeof(char));
//    if (new->item.identifier == NULL)
//    {
//        return NULL;
//    }

    // initialize the new node
    new->item.identifier = key;
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
                exit(1); // token of unknown type (not fit for symtab)
        }
    }

    // insert into the table
    size_t hash = htab_hash_function(key) % t->arr_size;
    new->next = t->arr_ptr[hash];
    t->arr_ptr[hash] = new;

    t->size++;
    return &new->item;
}


size_t htab_size(const htab_t * t)
{
    return t->size;
}