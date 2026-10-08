#ifndef FG_GRAPH_H
#define FG_GRAPH_H
#include <stddef.h>
typedef struct { int *items; size_t len, cap; } NeighborList;
typedef struct { NeighborList *adj; size_t n, cap; } Graph;
void graph_init(Graph *g); void graph_free(Graph *g); int add_user(Graph *g); int add_edge(Graph *g,int a,int b); int remove_edge(Graph *g,int a,int b); int are_friends(const Graph *g,int a,int b); size_t mutual_friends(const Graph *g,int a,int b,int *out,size_t out_cap);
#endif
