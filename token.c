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

typedef struct {
  closure* f;
  tokenizer* t;
} tokenizerc;

tokenizerc* newtokenizerc(void* f, tokenizer* t) {
  tokenizerc* c = malloc(sizeof(tokenizerc));
  c->f = f;
  c->t = t;
  return c;
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

token* opmmatch(void* this, list* s) {
  if(*(char*)s->head->data != '(') return nil;
  tokenizerc* c = this;
  c->t->balance++;
  listpop(s);
  return newtoken(newstring("("), newstring("("));
}

token* cpmmatch(void* this, list* s) {
  if(*(char*)s->head->data != ')') return nil;
  tokenizerc* c = this;
  c->t->balance--;
  listpop(s);
  return newtoken(newstring(")"), newstring(")"));
}

token* symmatch(void* this, list* s) {
  char* head = s->head->data;
  if(*head == '(' || *head == ')' || ws(*head)) return nil;
  listpop(s);
	if(!*head) return nil;
  list* l = newlist();
  listadd(l, newchar(*head));
	
  for(char* c = listnth(s, 0);;c = listnth(s, 0)) {
    if(!*c || ws(*c) || *c=='(' || *c== ')') break;
    listpop(s);
    listadd(l, newchar(*c));
  }

  listadd(l, newchar('\0'));
  char* val = listtostr(l);
  listwalk(l, free);
  listdelete(l);
  token* r = newtoken(newstring(val), newstring("symbol")); 
  free(val);
  return r;
}

char* newchar(char c) {
  char* n = malloc(sizeof(char));
  *n = c;
  return n;
}

tokenizer* newtokenizer() {
  tokenizer* t = malloc(sizeof(tokenizer));
	t->balance = 0;
	t->tokenize = (void*)tokenize;
  t->matchers = newlist();
  return t;
}

tokenizer* gsnewtokenizer() {
  tokenizer* t = newtokenizer();
  t->balance = 0;
  listadd(t->matchers, newtokenizerc(&opmmatch, t));
  listadd(t->matchers, newtokenizerc(&cpmmatch, t));
  listadd(t->matchers, newtokenizerc(&symmatch, t));
  return t;
}

token* searchmatch(tokenizer* t, list* s) {
  for(cell* c = t->matchers->head; c; c = c->next) {
    closure* f = c->data;
    token* t = closurecall(f, s);
    if(t) return t;
  }
  return nil;
}

void removews(list* s) {
  for(;;listpop(s)) {
    char* s0 = listnth(s, 0);
    if(!s0 || !ws(*s0)) return;
  }
}

list* tokenize(tokenizer* t, list* s) {
  list* tks = newlist();
  for(;s->length;) {
    removews(s);
    if(!s->length) break;
    token* tk = searchmatch(t, s);
    if(!t) return tks;
    listadd(tks, tk);
    if(!t->balance) break;
  }
  return tks;
}

token* tokencopy(token* t) {
	return newtoken(newstring(t->val->val), newstring(t->type->val));
}

void tokenizerdelete(tokenizer* t) {
  listwalk(t->matchers, free);
  listdelete(t->matchers);
  free(t);
}
