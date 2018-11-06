#ifdef POSIX

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "str.h"
#include "eval.h"

typedef void (*consumer)(void*);

void runmodule(trie* env, void* handle) {
    consumer mf = dlsym(handle, "init");
    mf(env);
}

void loadmodule(envc* this, list* args) {
	sexp* s = listpop(args);
	token* t = s->data;
	string* lib = t->val;
	tokenprint(t);
	void* handle = dlopen(lib->val, RTLD_LAZY);
	addto(this->env, "modules", lib->val, handle);
	runmodule(this->env, handle);
	free(s);
	free(t);
	free(lib);
}

#endif
