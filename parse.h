#ifndef PARSE_H
#define PARSE_H

#include "closure.h"
#include "list.h"
#include "token.h"
#include "trie.h"
#include "list.h"

typedef struct sexp sexp; 
typedef struct parser parser;

typedef sexp* (*pfn)(closure, list*);

struct parser {
	closure parse;
	trie* strats;
};

typedef struct {
	closure fn;
	parser* p;
} pstrat;

enum stypes {
	list_t,
	token_t
};

struct sexp {
	int type;
	void* data;
};

parser* newparser(void* fn);

sexp* symp(closure p, list* tks);

sexp* opp(closure p, list* tks);

void addstrat(parser* p, const char* name, pfn f);

pstrat* newpstrat(parser* p, pfn f);

sexp* parse(parser* p, list* tks);

#endif
