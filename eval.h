#ifndef EVAL_H
#define EVAL_H

#include "parse.h"

typedef struct {
	int type;
	void* data;
} o;

o* eval(sexp* s);

#endif
