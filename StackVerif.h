#ifndef STACKVERIF_H
#define STACKVERIF_H

#include <stdlib.h>

#include "StackStruct.h"

int StackVerif(StackStruct* Stack, size_t CallLineNum, const char* CallFile);

#define VERIF(arg) do {                     \
    StackVerif(arg, __LINE__, __FILE__);    \
} while(0)

#endif