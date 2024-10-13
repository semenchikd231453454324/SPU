#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "StackCtor.h"
#include "StackStruct.h"

int StackCtor(StackStruct* Stack)
{
    assert(Stack);

    Stack->Capacity = InitialStackCapacity;

    Stack->LeftStructCanary  = StructCanariesValue;
    Stack->RightStructCanary = StructCanariesValue;

    if(Stack->Capacity == 0)
    {
        Stack->Errors = Stack->Errors | StackCapacityZero;
        return 1;
    }

    Stack->LeftStackDataCanaryPointer = (elem_t*) calloc((Stack->Capacity + 2), sizeof(elem_t));
    if (!Stack->LeftStackDataCanaryPointer)
    {
        Stack->Errors = Stack->Errors | PointerStackDataFailureInCtor;
        return 1;
    }

    Stack->StackData = (elem_t*) ((char*) Stack->LeftStackDataCanaryPointer + sizeof(elem_t));
    Stack->RightStackDataCanaryPointer = (elem_t*) ((char*) Stack->LeftStackDataCanaryPointer + ((Stack->Capacity + 1) * sizeof(elem_t)));
    
    *(Stack->LeftStackDataCanaryPointer)  = StackDataCanariesValue;
    *(Stack->RightStackDataCanaryPointer) = StackDataCanariesValue;

    return 0;
}