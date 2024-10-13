#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "StackPush.h"
#include "StackStruct.h"
#include "recalloc.h"

void StackPush(StackStruct* Stack, int NewElem)
{
    assert(Stack);

    Stack->StackData[Stack->Size] = NewElem;

    Stack->Size++;

    if(Stack->Size == Stack->Capacity)
    {
       if((Stack->LeftStackDataCanaryPointer = (elem_t*) recalloc(Stack->LeftStackDataCanaryPointer, (Stack->Capacity)*2, sizeof(elem_t), Expand)) == nullptr)
       {
           Stack->Errors = Stack->Errors | recallocPushFailure;
       }
        
        Stack->Capacity = (Stack->Capacity)*2;
        Stack->StackData = (elem_t*) ((char*) Stack->LeftStackDataCanaryPointer + sizeof(elem_t));
        Stack->RightStackDataCanaryPointer = (elem_t*) ((char*) Stack->StackData + (sizeof(elem_t)*(Stack->Capacity)));
        *(Stack->RightStackDataCanaryPointer) = StackDataCanariesValue;
    }

}