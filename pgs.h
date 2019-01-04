#ifndef PGS_H
#define PGS_H

#include "trie.h"
#include "token.h"
#include "parse.h"
#define nil ((void*)0)

typedef struct {
	void* a;
	void* b;
} couple;

typedef struct {
	void* a;
	void* b;
} triple;

trie* newenv();

void envdelete(trie* env);

#endif
