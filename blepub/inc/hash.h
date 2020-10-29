#ifndef __HASH_H__
#define __HASH_H__

typedef struct _bucket 
{
    char* key;
    char* value;
    struct _bucket* next;
} item;

typedef struct
{
    item* buckets;
} hash_table;

int hash_init(hash_table **hash);
unsigned int hash_index(char *str);
int hash_insert(hash_table *hash, char *key, char *value);
int hash_renew(hash_table *hash, char *key, char *value);
int hash_find(hash_table *hash, char *key, item **bucket);
int hash_remove(hash_table *hash, char *key);
void hash_free(hash_table *hash);
#endif
