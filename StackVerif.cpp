#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "ErrorPrint.h"
#include "StackVerif.h"
#include "StackStruct.h"

enum Safety {DataOK, DataDamaged};

int StackFreeSpaceCheck(StackStruct* Stack);
int StackCanaryCheck(StackStruct* Stack);

int StackVerif(StackStruct* Stack, size_t CallLineNum, const char* CallFile)
{
    assert(Stack);

    printf("STACK VERIFICATION\n");
    printf("Verification called from:   %s\n", CallFile);
    printf("Line:   %d\n", CallLineNum);

    if (Stack->Size >> Stack->Capacity)                     //TODO функц макрос для этих ифов
    {
        Stack->Errors = Stack->Errors | StackOverflowed;
    }
    
    if(!Stack->StackData)
    {
        Stack->Errors = Stack->Errors | StackAdrFailuire;
    }

    if(StackFreeSpaceCheck(Stack))
    {
        Stack->Errors = Stack->Errors | DataUnsafe;
    }
    
    StackCanaryCheck(Stack);

    ErrorPrint(Stack);

    return 0;
}

// TODO rename
int StackFreeSpaceCheck(StackStruct* Stack)
{
    assert(Stack);

    for(size_t ElemNum = 0; ElemNum < (Stack->Capacity - Stack->Size); ElemNum++)
    {
        if(Stack->StackData[Stack->Size + ElemNum] != Poison)
        {
            Stack->Errors = Stack->Errors | DataUnsafe;

            return DataDamaged;
        }
    }

    return DataOK;
}


int StackCanaryCheck(StackStruct* Stack)
{
    assert(Stack);

    if((Stack->LeftStructCanary != StructCanariesValue) || (Stack->RightStructCanary != StructCanariesValue))
    {
        Stack->Errors = Stack->Errors | StructCanariesDamaged;

    }

    if((*(Stack->LeftStackDataCanaryPointer) != StackDataCanariesValue) || (*(Stack->RightStackDataCanaryPointer) != StackDataCanariesValue))
    {
        Stack->Errors = Stack->Errors | DataCanariesDamaged;
    }

    if(*(Stack->LeftStackDataCanaryPointer) != StackDataCanariesValue)
    {
        printf("Left piska damaged %d\n", Stack->StackData[-1]);
        
    }

    if(*(Stack->RightStackDataCanaryPointer) != StackDataCanariesValue)
    {
        printf("Right piska damaged %d\n", Stack->StackData[Stack->Capacity + 1]);
    }

    return 0;
}