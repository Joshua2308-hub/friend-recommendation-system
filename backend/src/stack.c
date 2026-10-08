#include "stack.h"
#include <stdlib.h>
/* O(1) */ void stack_init(UndoStack*s){s->a=NULL;s->len=s->cap=0;}
/* O(N) */ void stack_free(UndoStack*s){free(s->a);stack_init(s);}
/* Amortized O(1) */ int stack_push(UndoStack*s,UndoAction x){if(s->len==s->cap){size_t c=s->cap?s->cap*2:8;UndoAction*p=realloc(s->a,c*sizeof(*p));if(!p)return 0;s->a=p;s->cap=c;}s->a[s->len++]=x;return 1;}
/* O(1) */ int stack_pop(UndoStack*s,UndoAction*x){if(!s->len)return 0;*x=s->a[--s->len];return 1;}
