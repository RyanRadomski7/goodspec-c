#ifndef STRING_H
#define STRING_H

#include <stdlib.h>

typedef struct {
	char* val;
	int length;
} string;

string* newstring(char* s);
void stringdelete(string* s);
void stringprint(string* s);
int slen(char* s);

#endif
