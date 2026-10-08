#ifndef FG_UNIONFIND_H
#define FG_UNIONFIND_H
#include <stddef.h>
typedef struct { int *parent,*rank; size_t n; } UnionFind;
int uf_init(UnionFind *u,size_t n); void uf_free(UnionFind *u); int uf_find(UnionFind *u,int x); int uf_union(UnionFind *u,int a,int b); size_t uf_components(UnionFind *u);
#endif
