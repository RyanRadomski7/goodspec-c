#include <stdio.h>
#include "parse.h"

void parsetoken(parserholder* ph, token* t) {
	int (*fn)(parser*, list*, list*);	
	fn = trieget(ph->p->parsers, t->type->val);
	fn(ph->p, ph->tks, ph->ast);
}

parser* newparser() {
	parser* p = malloc(sizeof(p));
	p->parsers = newtrie();
	return p;
}

void parsedelete(parser* p) {
	triedelete(p->parsers);
}

