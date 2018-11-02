#ifndef CLOSURE_H
#define CLOSURE_H

typedef void* (*closure)(void*, void*);

void* closurecall(closure* c, void* a);

#endif
