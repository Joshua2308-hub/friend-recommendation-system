#include "queue.h"
#include <stdlib.h>
/* O(capacity) */ int queue_init(Queue*q,size_t n){q->data=malloc((n?n:1)*sizeof(int));if(!q->data)return 0;q->cap=n?n:1;q->head=q->len=0;return 1;}
/* O(1) */ void queue_free(Queue*q){free(q->data);q->data=NULL;q->cap=q->head=q->len=0;}
/* Amortized O(n) when growth is required */ int queue_push(Queue*q,int v){if(q->len==q->cap){size_t c=q->cap*2;int*p=malloc(c*sizeof(int));if(!p)return 0;for(size_t i=0;i<q->len;i++)p[i]=q->data[(q->head+i)%q->cap];free(q->data);q->data=p;q->cap=c;q->head=0;}q->data[(q->head+q->len++)%q->cap]=v;return 1;}
/* O(1) */ int queue_pop(Queue*q,int*v){if(!q->len)return 0;*v=q->data[q->head];q->head=(q->head+1)%q->cap;q->len--;return 1;}
