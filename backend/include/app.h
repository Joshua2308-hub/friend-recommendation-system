#ifndef FG_APP_H
#define FG_APP_H
#include "graph.h"
#include "recommend.h"
#include "hashtable.h"
#include "stack.h"
extern Graph fg_graph; extern FGUser fg_users[128]; extern size_t fg_user_count; extern HashTable fg_names; extern UndoStack fg_undo;
typedef struct { int id,from,to,status; } FGRequest; /* status 0 pending, 1 accepted, -1 declined, -2 cancelled */
extern FGRequest fg_requests[512]; extern size_t fg_request_count; extern int fg_current_user;
extern char fg_data_dir[256]; extern char fg_frontend_dir[256];
void ensure_data_dir(void);
int app_seed(void); int server_run(unsigned short port);
#endif

