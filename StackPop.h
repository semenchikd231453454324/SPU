#ifndef STACKPOP_H
#define STACKPOP_H

#include "StackStruct.h"

#define specifier "%d"
#define StackPopprint printf("Stack Elem %d = %d\n\n", Stack.Size, StackPop(&Stack))

int StackPop(StackStruct* Stack);

#endif