#ifndef TOKEN_H
#define TOKEN_H

#include "str.h"
#include "list.h"

typedef struct {
	string* val;
	string* type;
} token;

typedef struct {
	token* (*match)(void*, char*);
} matcher;

token* newtoken(string* val, string* type);
token* newtokenc(char* val, char* type);
token* match(matcher* m, char* s);

void tokendelete(token* m);
void tokenprint(token* t);
void tokenprints(token* t);

typedef struct {
	list* matchers;
} tokenizer;

tokenizer* newtokenizer();
tokenizer* gsnewtokenizer();

token* opmmatch(char* s);
token* cpmmatch(char* s);
token* symmatch(char* s);

list* tokenize(tokenizer* t, char* s);

void tokenizerdelete(tokenizer* t);

#endif
