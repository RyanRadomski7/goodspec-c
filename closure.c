#include "closure.h"

void* closurecall(closure c, void* a) {
	return c(c, a);
}
