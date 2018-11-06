#include <stdlib.h>
#include <stdio.h>
#include "token.h"

token* newtoken(string* val, string* type) {
	token* t = malloc(sizeof(token));
	t->val = val;
	t->type = type;
	return t;
}

token* newtokenc(char* val, char* type) {
	return newtoken(newstring(val), newstring(type));
}

token* match(matcher* m, char* s) {
	return ((token*(*)(void*))m)(s);
}

void tokendelete(token* m) {
	stringdelete(m->val);
	stringdelete(m->type);
	free(m);
}

void tokenprint(token* t) {
	const char* msg = "{type: \"%s\", val: \"%s\"}\n";
	printf(msg, t->type->val, t->val->val);
}

#define ws(c) (c==' '||c=='\t'||c=='\n'||c=='\v'||c=='\f'||c=='\r')

token* opmmatch(char* s) {
	if(*s != '(') return nil;
	return newtoken(newstring("("), newstring("("));
}

token* cpmmatch(char* s) {
	if(*s != ')') return nil;
	return newtoken(newstring(")"), newstring(")"));
}

char* newchar(char c) {
	char* n = malloc(sizeof(char));
	*n = c;
	return n;
}

char* listtostr(list* l) {
	char* a = malloc(l->length + 1);
	int i=0;
	for(cell* c = l->head; c; c = c->next) {
		a[i] = *(char*)(c->data);
		i++;
	}
	return a;
}

token* symmatch(char* s) {
	if(s[0] == '(' || s[0] == ')' || ws(s[0])) return nil;
	list* l = newlist();
	listadd(l, newchar(s[0]));
	for(int i = 1; s[i] && !ws(s[i]); i++) {
		if(s[i] == '(' || s[i] == ')') break;
		listadd(l, newchar(s[i]));
	}
	listadd(l, newchar('\0'));
	char* val = listtostr(l);
	listwalk(l, free);
	listdelete(l);
	token* r = newtoken(newstring(val), newstring("symbol")); 
	free(val);
	return r;
}

tokenizer* newtokenizer() {
	tokenizer* t = malloc(sizeof(tokenizer));
	t->matchers = newlist();
	return t;
}

tokenizer* gsnewtokenizer() {
	tokenizer* t = newtokenizer();
	listadd(t->matchers, (void*)&opmmatch);
	listadd(t->matchers, (void*)&symmatch);
	listadd(t->matchers, (void*)&cpmmatch);
	return t;
}

list* tokenize(tokenizer* t, char* s) {
	list* tokens = newlist();
	for(char* sp = s; *sp;) {
		for(;ws(*sp) && (*sp); sp++);
		s = sp;
		for(cell* c = t->matchers->head; c && *sp; c = c->next) {
			token* tp = match(c->data, sp);
			if(!tp) continue;
			listadd(tokens, tp);
			sp += tp->val->length;
		}
	}
	return tokens;
}

void tokenizerdelete(tokenizer* t) {
	listdelete(t->matchers);
	free(t);
}
