#ifdef POSIX

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "str.h"
#include "eval.h"
#include "util.h"

void runmodule(trie* env, void* handle) {
    consumer mf = dlsym(handle, "init");
    mf(env);
}

void runmoduleclose(trie* env, void* handle) {
    consumer mf = dlsym(handle, "close");
    mf(env);
}

void* getmodule(envc* this, string* lib) {
	trie* modules = trieget(this->env, "modules");
	return trieget(modules, lib->val);
}

void* popmodule(envc* this, string* lib) {
	trie* modules = trieget(this->env, "modules");
	return triepop(modules, lib->val);
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
	void* handle = popmodule(this, strarg1(args));
	runmoduleclose(this->env, handle);
	dlclose(handle);
}

#endif
