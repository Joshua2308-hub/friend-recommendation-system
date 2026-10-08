#include "json.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
/* Amortized O(1) */ static int reserve(JsonBuf*b,size_t n){if(b->len+n+1<=b->cap)return 1;size_t c=b->cap?b->cap:128;while(c<b->len+n+1)c*=2;char*p=realloc(b->data,c);if(!p)return 0;b->data=p;b->cap=c;return 1;}
/* O(1) */ int jb_init(JsonBuf*b){b->data=NULL;b->len=b->cap=0;return reserve(b,0);}
/* O(1) */ void jb_free(JsonBuf*b){free(b->data);b->data=NULL;b->len=b->cap=0;}
/* O(length of string) */ int jb_add(JsonBuf*b,const char*s){size_t n=strlen(s);if(!reserve(b,n))return 0;memcpy(b->data+b->len,s,n+1);b->len+=n;return 1;}
/* O(1) */ int jb_char(JsonBuf*b,char c){if(!reserve(b,1))return 0;b->data[b->len++]=c;b->data[b->len]=0;return 1;}
/* O(length of string) */ int jb_quote(JsonBuf*b,const char*s){if(!jb_char(b,'"'))return 0;for(;*s;s++){unsigned char c=(unsigned char)*s;if(c=='"'||c=='\\'){if(!jb_char(b,'\\')||!jb_char(b,(char)c))return 0;}else if(c<32){if(!jb_printf(b,"\\u%04x",c))return 0;}else if(!jb_char(b,(char)c))return 0;}return jb_char(b,'"');}
/* O(formatted output length) */ int jb_printf(JsonBuf*b,const char*fmt,...){va_list ap;va_start(ap,fmt);va_list cp;va_copy(cp,ap);int n=vsnprintf(NULL,0,fmt,cp);va_end(cp);if(n<0||!reserve(b,(size_t)n)){va_end(ap);return 0;}vsnprintf(b->data+b->len,b->cap-b->len,fmt,ap);va_end(ap);b->len+=(size_t)n;return 1;}
