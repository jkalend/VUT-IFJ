#include "htab.h"

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
            free((void *)head->item.key);
            free(head);
            head = t->arr_ptr[i];
        }
    }
    t->size = 0;
}

bool htab_erase(htab_t * t, htab_key_t key)
{
    size_t hash = htab_hash_function(key) % t->arr_size;

    htab_item_t *head = t->arr_ptr[hash];

    if (head == NULL) return false;
    else if (strcmp(head->item.key, key) == 0)
    {
        t->arr_ptr[hash] = head->next;
        free((void *)head->item.key);
        free(head);

        t->size--;
        return true;
    }
    else 
    {
        htab_item_t *delete = NULL;
        while (head->next != NULL)
        {
            if (strcmp(head->next->item.key, key) == 0)
            {
                delete = head->next;
                head->next = head->next->next;
                free((void *)delete->item.key);
                free(delete);

                t->size--;
                return true;
            }
            head = head->next;
        }
    }

    if (t->size / t->arr_size < AVG_LEN_MIN)
    {
        htab_resize(t, t->arr_size / 2);
    }

    return false;
}

htab_pair_t * htab_find(htab_t * t, htab_key_t key)
{
    size_t hash = htab_hash_function(key) % t->arr_size;

    // iterate over all table elements
    htab_item_t *head = t->arr_ptr[hash];
    while (head != NULL)
    {
        if (strcmp(head->item.key, key) == 0)
        {
            // the key was found
            return &head->item;
        }
        head = head->next;
    }
    // key not found
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


htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key)
{
    // check if the key exists in the table
    htab_pair_t *tmp = htab_find(t, key);
    if (tmp != NULL) 
    {
        tmp->value++;
        return tmp;
    }

    // if the new table size is greater, than the allowed average, resize it to twice its current size
    if ((t->size + 1) / t->arr_size > AVG_LEN_MAX)
    {
        htab_resize(t, 2 * t->arr_size);
    }
    
    //  dynamically allocate a new node
    htab_item_t *new = malloc(sizeof(htab_item_t));
    if (new == NULL)
    {
        return NULL;
    }
    new->item.key = malloc((strlen(key) + 1) * sizeof(char));
    if (new->item.key == NULL)
    {
        return NULL;
    }

    // initialize the new node
    strcpy((char *)new->item.key, key);
    new->next = NULL;
    new->item.value = 1;

    // insert into the table
    size_t hash = htab_hash_function(key) % t->arr_size;
    new->next = t->arr_ptr[hash];
    t->arr_ptr[hash] = new;

    t->size++;
    return &new->item;
}

void htab_resize(htab_t *t, size_t newn)
{
    if (newn <= 0)
        return;
        
    // the new size is bigger than the old, allocate more space
    if (newn >= t->arr_size)
    {
        htab_item_t **tmp = realloc(t->arr_ptr, newn * sizeof(htab_item_t *));
        if (tmp == NULL) return;
        t->arr_ptr = tmp;

        // initialize all newly added buckets
        for (size_t i = t->arr_size; i < newn; i++)
        {
            t->arr_ptr[i] = NULL;
        }
    }

    size_t old_size = t->arr_size;
    
    for (size_t i = 0; i < old_size; i++)
    {
        // iterate over all items in the old table and move all, whose hash value changed
        htab_item_t *head = t->arr_ptr[i];
        while (head != NULL)
        {
            // if the newly generated hash is different from the old one, move the element
            if ((htab_hash_function(head->item.key) % newn) != i)
            {    
                t->arr_size = newn;
                htab_pair_t *tmp = htab_lookup_add(t, head->item.key);
                t->size--;
                tmp->value = head->item.value;

                head = head->next;

                t->arr_size = old_size;
                htab_erase(t, tmp->key);
                continue;
            }
            head = head->next;
        }
    }

    // if the new size is smaller, free all (now redundant) space
    if (newn < t->arr_size)
    {
        htab_item_t **tmp = realloc(t->arr_ptr, newn * sizeof(htab_item_t *));
        if (tmp == NULL) return;
        t->arr_ptr = tmp;
    }
    t->arr_size = newn;
}



size_t htab_size(const htab_t * t)
{
    return t->size;
}