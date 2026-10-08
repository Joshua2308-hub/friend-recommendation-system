#include "unionfind.h"
#include <stdlib.h>
/* O(n) */ int uf_init(UnionFind*u,size_t n){u->parent=malloc((n?n:1)*sizeof(int));u->rank=calloc(n?n:1,sizeof(int));if(!u->parent||!u->rank){free(u->parent);free(u->rank);return 0;}u->n=n;for(size_t i=0;i<n;i++)u->parent[i]=(int)i;return 1;}
/* O(n) */ void uf_free(UnionFind*u){free(u->parent);free(u->rank);u->parent=u->rank=NULL;u->n=0;}
/* O(alpha(n)) amortized */ int uf_find(UnionFind*u,int x){if(!u||x<0||(size_t)x>=u->n)return -1;if(u->parent[x]!=x)u->parent[x]=uf_find(u,u->parent[x]);return u->parent[x];}
/* O(alpha(n)) amortized */ int uf_union(UnionFind*u,int a,int b){a=uf_find(u,a);b=uf_find(u,b);if(a<0||b<0)return 0;if(a==b)return 0;if(u->rank[a]<u->rank[b])u->parent[a]=b;else if(u->rank[a]>u->rank[b])u->parent[b]=a;else{u->parent[b]=a;u->rank[a]++;}return 1;}
/* O(n alpha(n)) */ size_t uf_components(UnionFind*u){size_t c=0;for(size_t i=0;i<u->n;i++)if(uf_find(u,(int)i)==(int)i)c++;return c;}
