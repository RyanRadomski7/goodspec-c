#include <stdlib.h>
#include <stdio.h>
#include "token.h"

token* newtoken(string* val, string* type) {
	token* t = malloc(sizeof(token));
	t->val = val;
	t->type = type;
	return t;
}

token* match(matcher* m, char* s) {
	return ((token*(*)(void*))m)(s);
}

void tokendelete(token* m) {
	stringdelete(m->val);
	stringdelete(m->type);
	free(m);
}

void tokenprint(token* t) {
	const char* msg = "{type: \"%s\", val: \"%s\"}\n";
	printf(msg, t->type->val, t->val->val);
}
