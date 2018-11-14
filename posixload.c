#ifdef POSIX

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "str.h"
#include "eval.h"
#include "util.h"

typedef void (*consumer)(void*);

void runmodule(trie* env, void* handle) {
    consumer mf = dlsym(handle, "init");
    mf(env);
}

void* getmodule(envc* this, string* lib) {
	trie* modules = trieget(this->env, "modules");
	return trieget(modules, lib->val);
}

void loadmodule(envc* this, list* args) {
	string* lib = strarg1(args);
	void* handle = dlopen(lib->val, RTLD_LAZY);
	addto(this->env, "modules", lib->val, handle);
	runmodule(this->env, handle);
}

int moduleloaded(envc* this, list* args) {
	void* h = getmodule(this, strarg1(args));
	return h!=nil;
}

void closemodule(envc* this, list* args) {
	dlclose(getmodule(this, strarg1(args)));
}

#endif
