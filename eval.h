#ifndef EVAL_H
#define EVAL_H

#include "parse.h"
#include "trie.h"

typedef struct {
	int type;
	void* data;
} o;

o* newo(int type, void* data);

typedef struct {
	closure f;
	trie* env;
} envc;

void* evalt(trie* env, token* t);
void* evall(trie* env, list* l);
void* eval(trie* env, sexp* s);

char* itos(int n);

envc* newenvc(void* f, void* env);

void addto(trie* env, char* n1, char* n2, void* d);

void* evals(envc* this, char* s);

trie* gsnewenv();

void gsenvdelete(trie* env);

#endif
