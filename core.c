#include <stdio.h>
#include "token.h"
#include "parse.h"
#include "trie.h"
#include "list.h"

#define list_t 0
#define sym_t  1

typedef struct {
	list* matchers;
} tokenizer;

#define ws(c) (c==' '||c=='\t'||c=='\n'||c=='\v'||c=='\f'||c=='\r')

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

token* opmmatch(char* s) {
	if(*s != '(') return nil;
	return newtoken(newstring("("), newstring("("));
}

token* cpmmatch(char* s) {
	if(*s != ')') return nil;
	return newtoken(newstring(")"), newstring(")"));
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

tokenizer* newtokenizer() {
	tokenizer* t = malloc(sizeof(tokenizer));
	t->matchers = newlist();
	return t;
}

void addmatcher(tokenizer* t, void* f) {
	listadd(t->matchers, (token*(*)(char*))f);
}

void tp(sexp* s) {
	tokenprint(s->data);
}

int main() {
	tokenizer* t = newtokenizer();
	addmatcher(t, &opmmatch);
	addmatcher(t, &cpmmatch);
	addmatcher(t, &symmatch);
	list* tks = tokenize(t, "(+ (+ 2 foobar) 5)");
	
	parser* p = newparser(parse);
	addstrat(p, "symbol", &symp);
	addstrat(p, "(", &opp);
	sexp* s = parse(p, tks);
	sexpprint(s);
	
	
	
	listwalk(tks, (void*)tokendelete);
	listdelete(tks);
	listdelete(t->matchers);
	free(t);
}
