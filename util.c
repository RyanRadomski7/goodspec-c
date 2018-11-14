#include "util.h"
#include "parse.h"
#include "str.h"
#include "list.h"

string* strarg1(list* args) {
	sexp* s = listnth(args, 0);
	return ((token*)s->data)->val;
}
