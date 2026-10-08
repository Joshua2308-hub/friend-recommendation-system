#ifndef FG_RECOMMEND_H
#define FG_RECOMMEND_H
#include "graph.h"
#include "heap.h"
#include "bfs.h"
#define FG_INTERESTS 8
#define FG_NAME 64
#define FG_HANDLE 32
typedef struct { char name[FG_NAME],handle[FG_HANDLE],interests[FG_INTERESTS][32]; int interest_count,blocked[128],blocked_count,declined[128],declined_count; } FGUser;
typedef struct { int id,mutual_count,score,distance,mutual_ids[128],path[128],path_len,mutual_points,distance_points,interest_points,penalty; } Recommendation;
size_t recommend_for_user(const Graph*g,const FGUser*u,size_t count,int source,int max_distance,int min_mutual,int limit,Recommendation*out);
#endif
