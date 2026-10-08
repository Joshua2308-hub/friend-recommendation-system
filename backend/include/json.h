#ifndef FG_JSON_H
#define FG_JSON_H
#include <stddef.h>
typedef struct { char *data; size_t len,cap; } JsonBuf;
int jb_init(JsonBuf*b); void jb_free(JsonBuf*b); int jb_add(JsonBuf*b,const char*s); int jb_char(JsonBuf*b,char c); int jb_quote(JsonBuf*b,const char*s); int jb_printf(JsonBuf*b,const char*fmt,...);
#endif
