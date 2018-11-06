#include "pgs.h"
#include "eval.h"

trie* newgs() {
	trie* env = gsnewenv();
	trieinsert(env, "p", gsnewparser());
	trieinsert(env, "t", gsnewtokenizer());
	return env;
}

void gsdelete(trie* env) {
	gsparserdelete(trieget(env, "p"));
	tokenizerdelete(trieget(env, "t"));
	gsenvdelete(env);
}
