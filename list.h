#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include "pgs.h"
#include "closure.h"

typedef struct cell cell;

struct cell {
	cell* next;
	void* data;
};

typedef struct {
	cell* head;
	cell* tail;
	int length;
} list;

list* newlist();
void listdelete(list* l);
void listdeepdelete(list* l, void* de);

void listadd(list* l, void* data);
void listpush(list* l, void* data);
void* listpoplast(list* l);
void* listpop(list* l);
void* listnth(list* l, int n);
void listwalk(list* l, void* f);
void listclosurewalk(list* l, closure* c);
void* listasarray(list* l);
list* listclosuremap(list* l, closure* c);

#endif
