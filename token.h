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
char* newchar(char c);
int tokenbalance(list* tks);

void tokendelete(token* m);
void tokenprint(token* t);
void tokenprints(token* t);
token* tokencopy(token* t);

typedef struct {
	list* (*tokenize)(void*, list*);
  int balance;
  list* matchers;
} tokenizer;

tokenizer* newtokenizer();
tokenizer* gsnewtokenizer();

token* opmmatch(void*, list* s);
token* cpmmatch(void*, list* s);
token* symmatch(void*, list* s);

list* tokenize(tokenizer* t, list* s);

void tokenizerdelete(tokenizer* t);

#endif
