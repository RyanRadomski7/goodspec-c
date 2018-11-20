#include "pgs.h"
#include "trie.h"
#include "list.h"
#include "token.h"
#include "parse.h"
#include "eval.h"

int main() {
	trie* env = newgs();
	char* exp = "(load ./add.o)(close ./add.o)";
	list* tks = tokenize(trieget(env, "t"), exp);

	while(tks->length) {
		sexp* s = parse(trieget(env, "p"), tks);
		eval(env, s);
	}

	listdelete(tks);
	gsdelete(env);
}
