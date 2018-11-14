#include <dlfcn.h>
#include <stdio.h>
#include "pgs.h"
#include "trie.h"
#include "list.h"
#include "token.h"
#include "parse.h"
#include "load.h"

int main() {
	trie* env = newgs();

	/* list* tks = tokenize(trieget(env, "t"), "(load ./add.o)"); */
	/* listwalk(tks, (void*)tokenprint); */

	/* sexp* s = parse(trieget(env, "p"), tks); */
	/* list* sl = s->data; */
	/* sexp* heads = sl->head->data; */
	/* tokenprint(heads->data); */
	/* envc* tr = evalt(env, heads->data); */
	/* closure* trc = (void*)tr; */
	/* printf("---------------------------------\n"); */
	/* sexpprint(s); */
	/* printf("---------------------------------\n"); */
	/* eval(env, s);	 */
	sexp* lt = newsexpt(newtokenc("load", "symbol"));
	sexp* at = newsexpt(newtokenc("./add.o", "symbol"));
	list* el = newlist();
	listadd(el, lt);
	listadd(el, at);
	sexp* s = newsexpl(el);
	/* eval(env, s); */
	sexpdelete(s);

	/* sexp* lt2 = newsexpt(newtokenc("close", "symbol")); */
	/* sexp* at2 = newsexpt(newtokenc("./add.o", "symbol")); */
	/* list* el2 = newlist(); */
	/* listadd(el2, lt2); */
	/* listadd(el2, at2); */
	/* sexp* s2 = newsexpl(el2); */
	/* eval(env, s2); */
	/* sexpdelete(s2); */

	/* listwalk(tks, (void*)tokendelete); */
	/* listdelete(tks); */
	gsdelete(env);
}
