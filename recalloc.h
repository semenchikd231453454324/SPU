#ifndef RECALLOC_H
#define RECALLOC_H

#include <stdlib.h>

void* recalloc(void* MemPointer, size_t ElementsNum, size_t SizeOfElement, int WorkScenario);

enum Variants {Expand, Reduce};

#endif