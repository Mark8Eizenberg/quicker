#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

typedef struct hash_table *hash_table_t;

hash_table_t ht_create(unsigned capacity, unsigned element_size);

unsigned ht_get_capacity(hash_table_t ht);

int ht_set_hash_function(hash_table_t ht, unsigned (*hash_function)(const char *, unsigned));

int ht_set(hash_table_t ht, const char *key, void *value);

void* ht_get(hash_table_t ht, const char *key);

int ht_remove(hash_table_t ht, const char *key);

void ht_set_is_rewrite_on_collision(hash_table_t ht, int is_rewrite_on_collision);

int ht_get_is_rewrite_on_collision(hash_table_t ht);

int ht_get_count(hash_table_t ht);

void ht_destroy(hash_table_t *ht);

#endif //_HASH_TABLE_H_