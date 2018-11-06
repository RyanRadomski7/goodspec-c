#ifdef POSIX

#include <dlfcn.h>
#include "str.h"
#include "eval.h"

typedef void (*consumer)(void*);

/* module register */
void mregister(trie* env, char* name, void* handle) {
	trie* modules = trieget(env, "modules");
	trieinsert(modules, name, handle);	
}

void runmodule(trie* env, void* handle) {
	consumer mf = dlsym(handle, "init");
	mf(env);
}

void loadmodule(envc* this, list* args) {
	string* lib = listpop(args);
	void* handle = dlopen(lib->val, RTLD_LAZY);
	mregister(this->env, lib->val, handle);		
}

#endif
