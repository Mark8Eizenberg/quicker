#include "hash_table.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct _hash_table_t
{
    __uint8_t *data;
    unsigned count;
    unsigned capacity;
    unsigned element_size;
    unsigned (*hash_function)(const char *, unsigned);
    int is_rewrite_on_collision;
};

#define TO_HASH_TABLE(x) ((struct _hash_table_t *)x)

static unsigned hash_function_default(const char *key, unsigned capacity)
{
    unsigned len = strlen(key);
    unsigned long hash = 0;
    while (len--)
    {
        hash = (hash << 5) + hash + (*key++);
    }
    return hash % capacity;
}

static void clean_hash_table(struct _hash_table_t *ht)
{
    if (ht == NULL)
        return;

    if (ht->data == NULL)
        return;

    ht->count = 0;
    memset(ht->data, 0, ht->capacity * ht->element_size);
}

hash_table_t ht_create(unsigned capacity, unsigned element_size)
{
    struct _hash_table_t *ht = (struct _hash_table_t *)malloc(sizeof(struct _hash_table_t));
    if (!ht)
        return NULL;

    ht->data = (__uint8_t *)malloc(capacity * element_size);
    if (!ht->data)
        goto free_ht;

    ht->capacity = capacity;
    ht->element_size = element_size;
    ht->hash_function = hash_function_default;
    ht->is_rewrite_on_collision = 0;
    clean_hash_table(ht);
    return (hash_table_t)ht;

free_ht:
    free(ht);
    return NULL;
}

unsigned ht_get_capacity(hash_table_t ht)
{
    if (ht == NULL)
        return 0;
    return TO_HASH_TABLE(ht)->capacity;
}

int ht_set_hash_function(hash_table_t ht, unsigned (*hash_function)(const char *, unsigned))
{
    if (ht == NULL)
        return -1;
    struct _hash_table_t *pht = TO_HASH_TABLE(ht);
    pht->hash_function = hash_function;
    clean_hash_table(pht);
    return 0;
}

static int is_data_free(struct _hash_table_t *ht, unsigned index)
{
    unsigned fact_index = index * ht->element_size;
    for (__uint8_t i = 0; i < ht->element_size; i++)
    {
        if (ht->data[fact_index + i] != 0)
            return 0;
    }

    return 1;
}

int ht_set(hash_table_t ht, const char *key, void *value)
{
    if (ht == NULL)
        return -1;

    struct _hash_table_t *pht = TO_HASH_TABLE(ht);
    unsigned index = pht->hash_function(key, pht->capacity);

    int is_memo_free = is_data_free(pht, index);

    if (! pht->is_rewrite_on_collision && ! is_memo_free)
    { 
        return -1;
    }

    memcpy(pht->data + index * pht->element_size, value, pht->element_size);
    if(is_memo_free)
        pht->count++;
    return 0;
}

void *ht_get(hash_table_t ht, const char *key)
{
    if (ht == NULL)
        return NULL;

    struct _hash_table_t *pht = TO_HASH_TABLE(ht);
    unsigned index = pht->hash_function(key, pht->capacity);
    if(is_data_free(pht, index))
        return NULL;
    return pht->data + index * pht->element_size;
}

int ht_remove(hash_table_t ht, const char *key)
{
    if(ht == NULL)
        return -1;
    
    struct _hash_table_t *pht = TO_HASH_TABLE(ht);
    unsigned index = pht->hash_function(key, pht->capacity);
    
    if (! is_data_free(pht, index)){
        pht->count--;
    }

    memset(pht->data + index * pht->element_size, 0, pht->element_size);
    return 0;
}

void ht_set_is_rewrite_on_collision(hash_table_t ht, int is_rewrite_on_collision)
{
    if (ht == NULL)
        return;

    TO_HASH_TABLE(ht)->is_rewrite_on_collision = is_rewrite_on_collision;
}

int ht_get_is_rewrite_on_collision(hash_table_t ht)
{
    if(ht == NULL) return -1;
    return TO_HASH_TABLE(ht)->is_rewrite_on_collision;
}

int ht_get_count(hash_table_t ht)
{
    if(ht == NULL) return -1;
    return TO_HASH_TABLE(ht)->count;
}

void ht_destroy(hash_table_t *ht)
{
    if (*ht == NULL) return;
    struct _hash_table_t *pht = TO_HASH_TABLE(*ht);
    if (pht->data) free(pht->data);
    free(pht);
    *ht = NULL;
}
