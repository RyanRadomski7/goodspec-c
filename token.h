#ifndef TOKEN_H
#define TOKEN_H

#include "str.h"

typedef struct {
	string* val;
	string* type;
} token;

typedef struct {
	token* (*match)(void*, char*);
} matcher;

token* newtoken(string* val, string* type);
token* match(matcher* m, char* s);
void tokendelete(token* m);
void tokenprint(token* t);
void tokenprints(token* t);

#endif
