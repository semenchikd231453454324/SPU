#ifndef STACKSTRUCT_H
#define STACKSTRUCT_H

#include <stdlib.h>

typedef int elem_t;
typedef long int canary_t;

#define specifier "%d"
#define StructCanariesValue 435
#define StackDataCanariesValue 78

#define printfStackElem printf("Stack->StackData[Stack->Size] = specifier\n", Stack->StackData[Stack->Size - 1])

enum SpecialValue {Poison = -1};

enum ErorrsValues 
{
    recallocPushFailure           = 1 << 0,
    StackCapacityZero             = 1 << 1,
    PointerStackDataFailureInCtor = 1 << 2,
    recallocPopFailure            = 1 << 3,
    DataUnsafe                    = 1 << 4,
    StackOverflowed               = 1 << 5,
    StackAdrFailuire              = 1 << 6,
    nullptrDataInFree             = 1 << 7,
    StructCanariesDamaged         = 1 << 8,
    DataCanariesDamaged           = 1 << 9
};

struct StackStruct
{
    canary_t LeftStructCanary;

    elem_t* StackData;
    elem_t* LeftStackDataCanaryPointer, *RightStackDataCanaryPointer;
    size_t Size, Capacity;

    int Errors;

    canary_t RightStructCanary;
};

#endif