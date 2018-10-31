#include "pgs.h"
#include "list.h"

list* newlist() {
	list* l = malloc(sizeof(list));
	l->head = nil;
	l->tail = nil;
	l->length = 0;
	return l;
}

cell* newcell(void* data) {
	cell* c = malloc(sizeof(cell));
	c->next = nil;
	c->data = data;
	return c;
}

void listdelete(list* l) {
	for(cell* c = l->head; c; c = l->head) listpop(l);
	free(l);
}

void listadd(list* l, void* data) {
	cell* add = newcell(data);
	if(l->head) {
		l->tail->next = add;
		l->tail = add;
	} else {
		l->head = add;
		l->tail = add;
	}
	l->length++;
}

void listpush(list* l, void* data) {
	cell* add = newcell(data);
	if(l->head) {
		add->next = l->head;
		l->head = add;
	} else {
		l->head = add;
		l->tail = add;
	}
	l->length++;
}

void* listpop(list* l) {
	cell* head = l->head;
	void* data = head->data;
	l->head = head->next;
	free(head);
	l->length--;
	return data;
}

void* listnth(list* l, int n) {
	cell* nthcell = l->head;
	for(int i = 0; i < n; i++) {
		if(!nthcell) return nil;
		nthcell = nthcell->next;
	}
	return nthcell ? nthcell->data : nil;
}

void listwalk(list* l, void (*f)(void* d)) {
	for(cell* c = l->head; c; c = c->next) f(c->data);
}

void* listasarray(list* l) {
	void** a = malloc(l->length * sizeof(void*)), **ap = a;
	for(cell* c = l->head; c; c = c->next) {
		*ap = c->data;
		ap++;
	}
	return (void*)a;
}
void listclosurewalk(list* l, closure f) {
	for(cell* c = l->head; c; c = c->next) f(f, c->data);
}
