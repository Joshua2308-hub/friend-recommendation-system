#include "recommend.h"
#include <assert.h>
#include <stdio.h>
/* O(V+E) on the fixed five-vertex fixture */
int main(void){Graph g;graph_init(&g);for(int i=0;i<5;i++)add_user(&g);add_edge(&g,0,1);add_edge(&g,0,2);add_edge(&g,1,3);add_edge(&g,2,3);add_edge(&g,3,4);FGUser u[5]={0};for(int i=0;i<5;i++){snprintf(u[i].name,sizeof u[i].name,"User %d",i);snprintf(u[i].interests[0],32,"coding");u[i].interest_count=1;}Recommendation r[5];size_t n=recommend_for_user(&g,u,5,0,3,0,5,r);assert(n==2);assert(r[0].id==3&&r[0].distance==2&&r[0].mutual_count==2);assert(r[0].score==45);assert(r[0].path_len==3);assert(r[0].path[0]==0&&r[0].path[2]==3);assert(r[1].id==4&&r[1].distance==3);graph_free(&g);return 0;}
