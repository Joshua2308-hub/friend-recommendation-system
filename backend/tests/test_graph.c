#include "graph.h"
#include "bfs.h"
#include "hashtable.h"
#include "heap.h"
#include "trie.h"
#include "unionfind.h"
#include "sort.h"
#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* O(V+E) across the small fixed test graph */ int main(void){
 Graph g;graph_init(&g);for(int i=0;i<6;i++)assert(add_user(&g)==i);
 assert(add_edge(&g,0,1)==1);assert(add_edge(&g,0,2)==1);assert(add_edge(&g,1,3)==1);assert(add_edge(&g,2,3)==1);assert(add_edge(&g,3,4)==1);assert(are_friends(&g,0,1));
 BFSResult b;assert(bfs_run(&g,0,3,&b));assert(b.dist[0]==0&&b.dist[3]==2&&b.dist[4]==3&&b.dist[5]==-1);assert(b.parent[4]==3);assert(b.trace_len>0);bfs_free(&b);
 int common[4];assert(mutual_friends(&g,1,2,common,4)==2&&common[0]==0&&common[1]==3);
 HashTable ht;ht_init(&ht,1);assert(ht_put(&ht,"alice",7));assert(ht_put(&ht,"david",8));assert(ht.collisions>=1);int v;assert(ht_get(&ht,"david",&v)&&v==8);assert(ht_load_factor(&ht)>0);ht_free(&ht);
 MaxHeap h;heap_init(&h);assert(heap_push(&h,(HeapItem){1,4}));assert(heap_push(&h,(HeapItem){2,12}));assert(heap_push(&h,(HeapItem){3,7}));HeapItem it;assert(heap_pop(&h,&it)&&it.score==12);heap_free(&h);
 Trie t;trie_init(&t);assert(trie_insert(&t,"alice"));assert(trie_insert(&t,"alina"));assert(trie_has_prefix(&t,"ali"));assert(!trie_has_prefix(&t,"zo"));trie_free(&t);
 UnionFind u;assert(uf_init(&u,6));uf_union(&u,0,1);uf_union(&u,1,2);uf_union(&u,3,4);assert(uf_components(&u)==3);uf_free(&u);
 int a[]={8,3,4,1,7};merge_sort(a,5);for(int i=1;i<5;i++)assert(a[i-1]<=a[i]);int z[]={9,-1,4,4,0};quick_sort(z,5);for(int i=1;i<5;i++)assert(z[i-1]<=z[i]);
 UndoStack st;stack_init(&st);assert(stack_push(&st,(UndoAction){1,2,1}));UndoAction action;assert(stack_pop(&st,&action)&&action.a==1&&action.b==2&&action.was_add);stack_free(&st);
 assert(remove_edge(&g,0,1));assert(!are_friends(&g,0,1));graph_free(&g);puts("All FriendGraph core tests passed.");return 0;
}
