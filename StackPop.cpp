#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "StackPop.h"
#include "StackStruct.h"
#include "recalloc.h"

int StackPop(StackStruct* Stack)
{
    assert(Stack);

    Stack->Size--;

    int TemporaryBuffer = Stack->StackData[Stack->Size];
    Stack->StackData[Stack->Size] = Poison;

    if(Stack->Size <= (Stack->Capacity) / 4)  // FIXME
    {
       if((Stack->LeftStackDataCanaryPointer = (elem_t*) recalloc(Stack->LeftStackDataCanaryPointer, (Stack->Capacity) / 4, sizeof(elem_t), Reduce)) == nullptr) 
       {
           Stack->Errors = Stack->Errors | recallocPopFailure;
       }

       Stack->Capacity = Stack->Capacity / 4;
       Stack->StackData = (elem_t*) ((char*) Stack->LeftStackDataCanaryPointer +  sizeof(elem_t));
       Stack->RightStackDataCanaryPointer = (elem_t*) ((char*) Stack->StackData + (sizeof(elem_t)*(Stack->Capacity - 2)));
       *(Stack->RightStackDataCanaryPointer) = StackDataCanariesValue;

    }

    return TemporaryBuffer;

} 
