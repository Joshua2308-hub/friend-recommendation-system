#ifndef FG_TRIE_H
#define FG_TRIE_H
typedef struct TrieNode TrieNode; typedef struct { TrieNode *root; } Trie;
void trie_init(Trie *t); void trie_free(Trie *t); int trie_insert(Trie *t,const char *word); int trie_has_prefix(const Trie *t,const char *prefix);
#endif
