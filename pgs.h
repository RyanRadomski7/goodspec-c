#ifndef PGS_H
#define PGS_H

#include "trie.h"
#define nil ((void*)0)

typedef struct {
	void* a;
	void* b;
} couple;

typedef struct {
	void* a;
	void* b;
} triple;

trie* newgs();

void gsdelete(trie* env);

#endif
