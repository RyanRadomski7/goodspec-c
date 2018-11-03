#include "eval.h"

o* evalt(token* t) {
	return nil;
}

o* evall(list* l) {
	return nil;
}

o* eval(sexp* s) {
	if(s->type == list_t) return evall(s->data);
	return evalt(s->data);
}
