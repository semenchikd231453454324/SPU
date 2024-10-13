#ifndef ERRORPRINT_H
#define ERRORPRINT_H

#include "StackStruct.h"

#define printfErr(arg, desc) do {      \
    if((Stack->Errors & arg) == arg)   \
    {                                  \
        printf(desc);                  \
    }                                  \
} while(0)

int ErrorPrint(StackStruct* Stack);                              

#endif