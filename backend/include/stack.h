#ifndef FG_STACK_H
#define FG_STACK_H
#include <stddef.h>
typedef struct { int a,b,was_add; } UndoAction; typedef struct { UndoAction *a; size_t len,cap; } UndoStack;
void stack_init(UndoStack *s); void stack_free(UndoStack *s); int stack_push(UndoStack *s,UndoAction x); int stack_pop(UndoStack *s,UndoAction *x);
#endif
