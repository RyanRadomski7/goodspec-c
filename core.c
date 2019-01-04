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

list* stol(char* s) {
	list* l = newlist();
	for(int i = 0; s[i]; i++) listadd(l, &s[i]);
	return l;
}

typedef struct {
	char* buf;
	int bs;
	int fd;
	list* tks;
	trie* env;
} reader;

void* envcall(trie* env, char* k, void* x) {
	return closurecall(trieget(env, k), x);
}

/* tokenize buffer */
void tbuf(reader* r) {
	list* code = stol(r->buf);
	for(;code->length;) 
		listconcat(r->tks, envcall(r->env, "t", code));
	listdelete(code);
}

int tokensvalid(reader* r) {
	list* tmp = listmap(r->tks, (void*)tokencopy);
	sexp* s = envcall(r->env, "p", tmp);
	int result = s != 0;
	if(s) sexpdelete(s);
	listdelete(listwalk(tmp, tokendelete));
	return result;
}

int prompt(reader* r) {
	if(!(read(r->fd, r->buf, r->bs) || r->tks->length)) return 0;
	tbuf(r);
	if(!tokensvalid(r)) return 1;
	for(sexp* s; r->tks->length && (s = envcall(r->env, "p", r->tks));)
		envcall(r->env, "e", s);
	return 1;
}

void readerdelete(reader* r) {
	listdelete(listwalk(r->tks, tokendelete));
	envdelete(r->env);
	free(r->buf);
}

int main(int argc, char* argv[]) {
	if(argc != 3) exit(EINVAL);
	reader r;
	r.fd = atoi(argv[1]);
	r.bs = atoi(argv[2]);
	r.buf = malloc(sizeof(char) * r.bs);
	r.tks = newlist();
	r.env = newenv();
	for(;prompt(&r););
	readerdelete(&r);
}
