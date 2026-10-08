#ifndef FG_HASHTABLE_H
#define FG_HASHTABLE_H
#include <stddef.h>
typedef struct HashEntry { char *key; int value; struct HashEntry *next; } HashEntry;
typedef struct { HashEntry **buckets; size_t capacity,size,collisions,max_chain; } HashTable;
void ht_init(HashTable *h,size_t cap); void ht_free(HashTable *h); int ht_put(HashTable *h,const char *key,int value); int ht_get(const HashTable *h,const char *key,int *value); double ht_load_factor(const HashTable *h);
#endif
