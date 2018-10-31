#include "trie.h"
#include <stdio.h>

trie* newtrie() {
	trie* t = malloc(sizeof(trie));
	t->root = nil;
	return t;
}

tnode* newnode(char k, void* data) {
	tnode* n = malloc(sizeof(tnode));
	n->next = nil;
	n->down = nil;
	n->k = k;
	n->data = nil;
	return n;
}	

void nodedelete(tnode* n) {
	if(!n) return;
	nodedelete(n->next);
	nodedelete(n->down);
	free(n);
}

tnode* nodeinlevel(tnode* n, char k) {
	if(!n) return nil;
	if(n->k == k) return n;
	return nodeinlevel(n->next, k);
}

tnode* nodeget(tnode* n, const char* k) {
	if(!n) return nil;
	tnode* f = nodeinlevel(n, *k);
	if(!f) return nil;
	if(f->k == *k && !*(k+1)) return f;
	return f ? nodeget(f->down, k+1) : nil;
}

void nodeprint(int indent, tnode* n) {
	if(!n) return;
	for(int i = 0; i < indent; i++) printf(" ");
	printf("%c\n", n->k);
	nodeprint(indent+1, n->down);
	nodeprint(indent, n->next);
}

void* nodepop(tnode* n) {
	void* data = n->data;
	n->data = nil;
	return data;
}

void* triepop(trie* t, const char* k) {
	if(!t) return nil;
	tnode* n = nodeget(t->root, k);
	if(!n) return nil;
	return nodepop(n);
}

void* trieget(trie* t, const char* k) {
	if(!t) return nil;
	tnode* n = nodeget(t->root, k);
	return n ? n : nil;
}

tnode* nodepush(tnode* n, char k) {
	tnode* f = newnode(k, nil);
	f->next = n;
	return f;
}

tnode* nodeinsert(tnode* n, const char* k, void* data) {
	tnode* f = nodeinlevel(n, *k);
	if(!f) f = nodepush(n, *k);
	if(*(k + 1)) f->down = nodeinsert(f->down, k + 1, data);
	else f->data = data;
	return f;
}

void trieinsert(trie* t, const char* k, void* data) {
	t->root = nodeinsert(t->root, k, data);
}

void triedelete(trie* t) {
	if(!t) return;
	nodedelete(t->root);
	free(t);
}
