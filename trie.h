#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>
#include "pgs.h"

typedef struct tnode tnode;

struct tnode {
	char k;
	tnode* next;
	tnode* down;
	void* data;
};

typedef struct {
	tnode* root;
} trie;

trie* newtrie();
void triedelete(trie* t);
void trieinsert(trie* t, const char* k, void* data);
void* trieget(trie* t, const char* k);
void* triepop(trie* t, const char* k);

#endif
