#include <stdio.h>
#include "pgs.h"
#include "trie.h"
#include "list.h"
#include "token.h"

int main() {
	trie* env = newgs();

	list* tks = tokenize(trieget(env, "t"), "(+ 1 2)");
	listwalk(tks, (void*)tokenprint);
	listwalk(tks, (void*)tokendelete);
	listdelete(tks);

	gsdelete(env);
}
