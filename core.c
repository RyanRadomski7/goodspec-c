#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pgs.h"
#include "trie.h"
#include "list.h"
#include "token.h"
#include "parse.h"
#include "eval.h"

typedef unsigned long lu;
tnode* nodepush(tnode* n, char k);
tnode* missing(tnode* n, const char* k, void* data);

int main(int argc, char* argv[]) {
	if(argc != 3) exit(EINVAL);
	int fd = atoi(argv[1]);
	int bs = atoi(argv[2]);
	char* buff = malloc(sizeof(char) * bs);
	trie* env = newgs();

	while(read(fd, buff, bs)) {
		list* tks = tokenize(trieget(env, "t"), buff);
		
		while(tks->length) {
			sexp* s = closurecall(trieget(env, "p"), tks);
			eval(env, s);
		}

		listdelete(tks);
	}
	
	gsdelete(env);
}
