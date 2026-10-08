#ifndef FG_REQUESTS_H
#define FG_REQUESTS_H
int request_create(int from,int to); int request_respond(int id,int actor,const char*action);
#endif
