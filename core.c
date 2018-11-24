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

/* void printchar(char* c) { */
/* 	printf("%c", *c); */
/* } */

int main(int argc, char* argv[]) {
	if(argc != 3) exit(EINVAL);
	int fd = atoi(argv[1]);
	int bs = atoi(argv[2]);
	char* buff = malloc(sizeof(char) * bs);
	trie* env = newgs();

	list* code = newlist();
	for(;read(fd, buff, bs);)
		for(char* c=buff; *c; c++)
			listadd(code, newchar(*c));

	list* codecopy = copy(code);
	for(;code->length;) {
		list* tks = tokenize(trieget(env, "t"), code);
		if(tks->length) {	
			sexp* s = closurecall(trieget(env, "p"), tks);
			sexpprint(s);
			eval(env, s);
		}
		listwalk(tks, tokendelete);
		listdelete(tks);
	}

	listwalk(codecopy, free);
	listdelete(code);
	listdelete(codecopy);
	free(buff);
	
	gsdelete(env);
}
