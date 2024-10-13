#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "StackDump.h"
#include "StackStruct.h"

void StackDump(StackStruct* Stack, size_t CallLineNum, const char* CallFile)
{
    assert(Stack);
    
    printf("Dump called from:   %s\n", CallFile);
    printf("Line:   %d\n", CallLineNum);
    printf("Stack Capacity = %d\n", Stack->Capacity);
    printf("Stack Size     = %d\n", Stack->Size);
    
    for(size_t ElemNum = 0; ElemNum < Stack->Capacity; ElemNum++)
    {
        printf("Stack Element %d = %d\n", ElemNum, Stack->StackData[ElemNum]);
    }

    printf("\n\n\n\n");
}