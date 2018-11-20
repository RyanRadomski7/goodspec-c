#include <stdio.h>
#include "trie.h"
#include "eval.h"

extern void init(trie* env) {
	printf("Loading add\n");
}

extern void close(trie* env) {
	printf("Closing add\n");
}
