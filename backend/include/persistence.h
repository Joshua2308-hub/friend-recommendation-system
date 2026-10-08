#ifndef FG_PERSISTENCE_H
#define FG_PERSISTENCE_H
#include "graph.h"
#include "app.h"
int persistence_load_users(FGUser*users,size_t*count); int persistence_load_edges(Graph*g); int persistence_save_edges(const Graph*g); int persistence_load_requests(void); int persistence_save_requests(void);
#endif
