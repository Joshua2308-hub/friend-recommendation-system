#ifndef FG_HEAP_H
#define FG_HEAP_H
#include <stddef.h>
typedef struct { int id,score; } HeapItem; typedef struct { HeapItem *a; size_t len,cap; } MaxHeap;
void heap_init(MaxHeap *h); void heap_free(MaxHeap *h); int heap_push(MaxHeap *h,HeapItem x); int heap_pop(MaxHeap *h,HeapItem *x); int heap_top_k(MaxHeap *h,size_t k,HeapItem *out,size_t *count);
#endif
