#include <dlfcn.h>
#include <stdio.h>
#include "pgs.h"
#include "trie.h"
#include "list.h"
#include "token.h"
#include "parse.h"
#include "load.h"

int main() {
	trie* env = newgs();

	list* tks = tokenize(trieget(env, "t"), "(load ./add.o)");
	listwalk(tks, (void*)tokenprint);

	sexp* s = parse(trieget(env, "p"), tks);
	list* sl = s->data;
	sexp* heads = sl->head->data;
	tokenprint(heads->data);
	envc* tr = evalt(env, heads->data);
	closure* trc = (void*)tr;
	printf("---------------------------------\n");
	sexpprint(s);
	printf("---------------------------------\n");
	eval(env, s);	

	listwalk(tks, (void*)tokendelete);
	listdelete(tks);
	gsdelete(env);
}
