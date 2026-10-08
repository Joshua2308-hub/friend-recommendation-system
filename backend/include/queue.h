#ifndef FG_QUEUE_H
#define FG_QUEUE_H
#include <stddef.h>
typedef struct { int *data; size_t cap,head,len; } Queue;
int queue_init(Queue *q,size_t cap); void queue_free(Queue *q); int queue_push(Queue *q,int v); int queue_pop(Queue *q,int *v);
#endif
