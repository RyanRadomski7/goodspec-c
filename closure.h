typedef void* (*closure)(void*, void*);

void* closurecall(closure c, void* a);
