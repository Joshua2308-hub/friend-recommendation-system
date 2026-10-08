#include "hashtable.h"
#include <stdlib.h>
#include <string.h>
/* O(key length) */ static unsigned long hash(const char*s){unsigned long h=5381;for(;*s;s++)h=h*33u+(unsigned char)*s;return h;}
/* O(capacity) */ void ht_init(HashTable*h,size_t cap){h->capacity=cap?cap:16;h->size=h->collisions=h->max_chain=0;h->buckets=calloc(h->capacity,sizeof(*h->buckets));}
/* O(N) */ void ht_free(HashTable*h){if(!h)return;if(h->buckets)for(size_t i=0;i<h->capacity;i++){HashEntry*e=h->buckets[i];while(e){HashEntry*n=e->next;free(e->key);free(e);e=n;}}free(h->buckets);h->buckets=NULL;h->capacity=h->size=0;}
/* O(N) */ static int resize(HashTable*h){size_t c=h->capacity*2;HashEntry**b=calloc(c,sizeof(*b));if(!b)return 0;for(size_t i=0;i<h->capacity;i++){HashEntry*e=h->buckets[i];while(e){HashEntry*n=e->next;size_t k=hash(e->key)%c;e->next=b[k];b[k]=e;e=n;}}free(h->buckets);h->buckets=b;h->capacity=c;h->max_chain=0;for(size_t i=0;i<c;i++){size_t n=0;for(HashEntry*e=b[i];e;e=e->next)n++;if(n>h->max_chain)h->max_chain=n;}return 1;}
/* Expected O(1), worst O(N); resizes over 0.75 load */ int ht_put(HashTable*h,const char*k,int v){if(!h||!k||!h->buckets)return 0;size_t i=hash(k)%h->capacity,chain=0;for(HashEntry*e=h->buckets[i];e;e=e->next){chain++;if(!strcmp(e->key,k)){e->value=v;return 1;}}if(chain)h->collisions++;HashEntry*e=malloc(sizeof(*e));if(!e)return 0;size_t n=strlen(k)+1;e->key=malloc(n);if(!e->key){free(e);return 0;}memcpy(e->key,k,n);e->value=v;e->next=h->buckets[i];h->buckets[i]=e;h->size++;if(chain+1>h->max_chain)h->max_chain=chain+1;if((double)h->size/h->capacity>0.75&&!resize(h))return 0;return 1;}
/* Expected O(1), worst O(N) */ int ht_get(const HashTable*h,const char*k,int*v){if(!h||!k||!h->buckets)return 0;for(HashEntry*e=h->buckets[hash(k)%h->capacity];e;e=e->next)if(!strcmp(e->key,k)){if(v)*v=e->value;return 1;}return 0;}
/* O(1) */ double ht_load_factor(const HashTable*h){return h&&h->capacity?(double)h->size/h->capacity:0.0;}
