#include "trie.h"
#include <stdlib.h>
#include <string.h>
struct TrieNode { struct TrieNode *child[128]; int terminal; };
/* O(1) */ void trie_init(Trie*t){t->root=calloc(1,sizeof(*t->root));}
/* O(total nodes) */ static void node_free(TrieNode*n){if(!n)return;for(int i=0;i<128;i++)node_free(n->child[i]);free(n);}
/* O(total nodes) */ void trie_free(Trie*t){node_free(t->root);t->root=NULL;}
/* O(L) */ int trie_insert(Trie*t,const char*w){if(!t->root)trie_init(t);TrieNode*n=t->root;for(;*w;w++){unsigned char c=(unsigned char)*w;if(c>=128)return 0;if(!n->child[c]){n->child[c]=calloc(1,sizeof(TrieNode));if(!n->child[c])return 0;}n=n->child[c];}n->terminal=1;return 1;}
/* O(L) */ int trie_has_prefix(const Trie*t,const char*p){if(!t||!t->root)return 0;TrieNode*n=t->root;for(;*p;p++){unsigned char c=(unsigned char)*p;if(c>=128||!n->child[c])return 0;n=n->child[c];}return 1;}
