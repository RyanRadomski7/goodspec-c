#include <stdlib.h>

typedef struct {
	char* val;
	int length;
} string;

string* newstring(char* s);
void stringdelete(string* s);
void stringprint(string* s);
