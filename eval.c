#include <stdio.h>
#include "eval.h"
#include "closure.h"
#include "load.h"

char* itos(int n) {
	int mag = 32, len, i;
	for(len = 1; mag <= n; len++) {
		mag *= 32;
	}
	char* s = malloc(len+1);
	mag /= 32;
	for(i = 0; i < len; i++) {
		s[i] = n / mag;
		n -= s[i] * mag;
		mag /= 32;
	}
	s[i] = '\0';
	return s;
}

o* newo(int type, void* data) {
	o* ob = malloc(sizeof(o));
	ob->type = type;
	ob->data = data;
	return ob;
}

void* evalt(trie* env, token* t) {
	trie* evals = trieget(env, "evals");
	closure* f = trieget(evals, t->type->val);
	return closurecall(f, t->val->val);
}

void* evall(trie* env, list* l) {
	void* fsexp = listpop(l);
	void* fn = eval(env, fsexp);
	free(fsexp);
	void* r = closurecall(fn, l);
	listdelete(l);
	return r;
}

void* eval(trie* env, sexp* s) {
	return s->type == token_t ?
		evalt(env, s->data) :
		evall(env, s->data);
}

envc* newenvc(void* f, void* env) {
	envc* ec = malloc(sizeof(envc));
	ec->f = f;
	ec->env = env;
	return ec;
}

void addto(trie* env, char* n1, char* n2, void* d) {
	trie* nested = trieget(env, n1);
	trieinsert(nested, n2, d);
}

void* evals(envc* this, char* s) {
	trie* symbols = trieget(this->env, "symbols");
	return trieget(symbols, s);
}

trie* gsnewenv() {
	trie* env = newtrie();
	trieinsert(env, "symbols", newtrie());
	trieinsert(env, "evals", newtrie());
	addto(env, "symbols", "load", newenvc(loadmodule, env));
	addto(env, "symbols", "close", newenvc(closemodule, env));
	addto(env, "evals", "symbol", newenvc(evals, env));
	return env;
}

void gsenvdelete(trie* env) {
	trie* symbols = triepop(env, "symbols");
	trie* evals = triepop(env, "evals");
	free(triepop(symbols, "load"));
	free(triepop(symbols, "close"));
	free(triepop(evals, "symbol"));
	triedelete(symbols);
	triedelete(evals);
	triedelete(env);
}
