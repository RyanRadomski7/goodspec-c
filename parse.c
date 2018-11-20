#include <stdio.h>
#include "parse.h"

sexp* newsexpt(token* t) {
	sexp* s = malloc(sizeof(sexp));
	s->type = token_t;
	s->data = t;
	return s;
}

sexp* newsexpl(list* l) {
	sexp* s = malloc(sizeof(sexp));
	s->type = list_t;
	s->data = l;
	return s;
}

void sexpdelete(sexp* s) {
	if(s->type == list_t) 
		listdeepdelete(s->data, sexpdelete);
	else tokendelete(s->data);
	free(s);
}

parser* newparser(void* fn) {
	parser* p = malloc(sizeof(parser));
	p->parse = fn;
	p->strats = newtrie();
	return p;
}

/* symbol parse */
sexp* symp(closure p, list* tks) {
	token* sym = listpop(tks);
	return newsexpt(sym);
}

/* close expression */
list* clsexp(list* exp, list* tks) {
	tokendelete(listpop(tks));
	return exp;
}

/* slurp expression */
list* slsexp(parser* p, list* exp, list* tks) {
	token* tk = tks->head->data;
	string* t = tk->type;
	if(t->length==1 && t->val[0]==')') 
		return clsexp(exp, tks);
	listadd(exp, closurecall(&p->parse, tks));
	return slsexp(p, exp, tks);
}

sexp* opp(closure this, list* tks) {
	pstrat* s = (pstrat*)this;
	tokendelete(listpop(tks));
	return newsexpl(slsexp(s->p, newlist(), tks));
}

pstrat* newpstrat(parser* p, pfn f) {
	pstrat* s = malloc(sizeof(pstrat));
	s->fn = (void*)f;
	s->p = p;
	return s;
}

void addstrat(parser* p, const char* name, pfn f) {
	trieinsert(p->strats, name, newpstrat(p, f));
}

sexp* parse(parser* p, list* tks) {
	token* t = tks->head->data;
	pstrat* s = trieget(p->strats, t->type->val);
	return closurecall((closure*)s, tks);
}

void sexpprintiter(sexp* s);

void sexpprintc(cell* c) {
	if(!c) return;
	sexpprintiter(c->data);
	if(c->next) printf(" ");
	sexpprintc(c->next);
}

void sexpprintl(list* l) {
	printf("(");
	sexpprintc(l->head);
	printf(")");
}

void sexpprintt(token* t) {
	printf("%s", t->val->val);
}

void sexpprintiter(sexp* s) {
	if(s->type == list_t) sexpprintl(s->data);
	else sexpprintt(s->data);
}

void sexpprint(sexp* s) {
	sexpprintiter(s);
	printf("\n");
}

parser* gsnewparser() {
	parser* p = newparser(parse);
	addstrat(p, "symbol", &symp);
	addstrat(p, "(", &opp);
	return p;
}

void gsparserdelete(parser* p) {
	free(triepop(p->strats, "symbol"));
	free(triepop(p->strats, "("));
	triedelete(p->strats);
	free(p);
}
