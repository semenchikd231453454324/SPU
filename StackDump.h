#ifndef STACKDUMP_H
#define STACKDUMP_H

#include <stdlib.h>

#include "StackStruct.h"

void StackDump(StackStruct* Stack, size_t CallLineNum, const char* CallFile);

#define DUMP(arg) do {                      \
    StackDump(arg, __LINE__, __FILE__);     \
} while(0)

#endif