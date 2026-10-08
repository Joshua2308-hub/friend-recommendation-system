#ifndef FG_BFS_H
#define FG_BFS_H
#include "graph.h"
typedef struct { int current; int *queue; int queue_len; int *visited; int visited_len; } BFSStep;
typedef struct { int *dist,*parent; BFSStep *trace; int trace_len; } BFSResult;
int bfs_run(const Graph *g,int source,int max_depth,BFSResult *out); void bfs_free(BFSResult *r);
#endif
