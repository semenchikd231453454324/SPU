#ifndef STACKDESTRUCT_H
#define STACKDESTRUCT_H

#include "StackStruct.h"

enum freeErrors {StackDestructed, nullptrInfree};

int StackDestruct(StackStruct* Stack);

#endif