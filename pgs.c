#include "pgs.h"
#include "eval.h"

trie* newenv() {
	trie* env = gsnewenv();
	trieinsert(env, "p", gsnewparser());
	trieinsert(env, "t", gsnewtokenizer());
	trieinsert(env, "e", newenvc(gsevaluator, env));
	return env;
}

void envdelete(trie* env) {
	gsparserdelete(trieget(env, "p"));
	tokenizerdelete(trieget(env, "t"));
	free(trieget(env, "e"));
	gsenvdelete(env);
}
