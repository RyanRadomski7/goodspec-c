#include "trie.h"
#include "list.h"
#include "token.h"

typedef struct {
	trie* parsers;
} parser;

typedef struct {
	closure f;
	parser* p;
	list* tks;
	list* ast;
} parserholder;

typedef struct {
	int type;
	void* data;
} sexp;

parser* newparser();
list* parse(parser* p, list* tks);
void parsedelete(parser* p);
void parsetoken(parserholder* ph, token* t);
