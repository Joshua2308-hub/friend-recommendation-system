#include "stats.h"
#include "sort.h"
#include <stdlib.h>
#include <time.h>
/* O(V log V) */ void stats_sort_times(const Graph*g,unsigned long long*m,unsigned long long*q){size_t n=g->n;int*a=malloc((n?n:1)*sizeof(int)),*b=malloc((n?n:1)*sizeof(int));if(!a||!b){free(a);free(b);*m=*q=0;return;}for(size_t i=0;i<n;i++)a[i]=b[i]=(int)g->adj[i].len;clock_t x=clock();merge_sort(a,n);clock_t y=clock();quick_sort(b,n);clock_t z=clock();*m=(unsigned long long)((double)(y-x)*1000000.0/CLOCKS_PER_SEC);*q=(unsigned long long)((double)(z-y)*1000000.0/CLOCKS_PER_SEC);free(a);free(b);}
