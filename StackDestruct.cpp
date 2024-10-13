#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "StackDestruct.h"
#include "StackStruct.h"

int StackDestruct(StackStruct* Stack)
{
    if (!Stack) {
        return StackDestructed;
    }

    Stack->Capacity = 0;
    Stack->Size     = 0;
    Stack->Errors   = 0;

    free(Stack->StackData);

    Stack->StackData = nullptr;

    return StackDestructed;
}