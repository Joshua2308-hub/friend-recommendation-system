#include "heap.h"
#include <stdlib.h>
/* O(1) */ void heap_init(MaxHeap*h){h->a=NULL;h->len=h->cap=0;}
/* O(N) */ void heap_free(MaxHeap*h){free(h->a);heap_init(h);}
/* O(log N) amortized */ int heap_push(MaxHeap*h,HeapItem x){if(h->len==h->cap){size_t c=h->cap?h->cap*2:8;HeapItem*p=realloc(h->a,c*sizeof(*p));if(!p)return 0;h->a=p;h->cap=c;}size_t i=h->len++;while(i&&h->a[(i-1)/2].score<x.score){h->a[i]=h->a[(i-1)/2];i=(i-1)/2;}h->a[i]=x;return 1;}
/* O(log N) */ int heap_pop(MaxHeap*h,HeapItem*x){if(!h->len)return 0;*x=h->a[0];HeapItem z=h->a[--h->len];if(h->len){size_t i=0;while(i*2+1<h->len){size_t c=i*2+1;if(c+1<h->len&&h->a[c+1].score>h->a[c].score)c++;if(h->a[c].score<=z.score)break;h->a[i]=h->a[c];i=c;}h->a[i]=z;}return 1;}
/* O(K log N) */ int heap_top_k(MaxHeap*h,size_t k,HeapItem*out,size_t*n){*n=0;while(*n<k&&*n<h->len)if(!heap_pop(h,&out[(*n)++]))return 0;return 1;}
