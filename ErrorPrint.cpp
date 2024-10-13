#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "StackStruct.h"
#include "ErrorPrint.h"

int ErrorPrint(StackStruct* Stack)
{
    assert(Stack);

    printfErr(recallocPushFailure, "Recalloc in push returned nullptr\n");

    printfErr(StackCapacityZero, "Can't create stack with zero capacity\n");

    printfErr(PointerStackDataFailureInCtor, "Calloc in StackCtor returned zero\n");
    
    printfErr(recallocPopFailure, "Recalloc in pop returned nullptr\n");
    
    printfErr(DataUnsafe, "Garbage in unoccupied space in StackData\n");
    
    printfErr(StackOverflowed, "Size of Stack > Capacity of Stack\n");
    
    printfErr(StackAdrFailuire, "Pointer to StackData is zero\n");

    printfErr(nullptrDataInFree, "In StackDestruct pointer to stack is zero\n");

    printfErr(StructCanariesDamaged, "Canaries protecting StackStruct are damaged\n");
    
    printfErr(DataCanariesDamaged, "Canaries protecting StackData are damaged\n");

    return 0;
}