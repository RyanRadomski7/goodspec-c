#include "str.h"
#include <stdio.h>

int slen(char* s) {
	int l;
	for(l = 0; s[l]; l++);
	return l;
}

string* newstring(char* s) {
	string* ns = malloc(sizeof(string));
	ns->length = slen(s);
	ns->val = malloc(sizeof(char) * (ns->length+1));
	for(int i = 0; i < ns->length+1; i++)
		ns->val[i] = s[i];
	return ns;
}

void stringdelete(string* s) {
	free(s->val);
	free(s);
}

void stringprint(string* s) {
	printf("{val: \"%s\", length: %d}\n", s->val, s->length);
}
