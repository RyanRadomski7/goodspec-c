#ifndef LOAD_H
#define LOAD_H

#include "eval.h"

void loadmodule(envc* this, list* args);
int moduleloaded(envc* this, list* args);
void closemodule(envc* this, list* args);

#endif
