#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "StackStruct.h"
#include "recalloc.h"

void* recalloc(void* MemPointer, size_t ElementsNum, size_t SizeOfElement, int WorkScenario) 
{
    assert(MemPointer);

    void* NemMemPointer = realloc(MemPointer, (ElementsNum*SizeOfElement + 2));

    if(NemMemPointer == nullptr)
    {
        return nullptr;
    }

    switch (WorkScenario)
    {
        case Expand:
        {

            void* MemPointerForMemset = (void*) ((char*) NemMemPointer + 4 + ((ElementsNum*SizeOfElement) / 2));

            memset( MemPointerForMemset, Poison, (ElementsNum*SizeOfElement) / 2);

            break;
        }

        case Reduce:
        {                              
            break;
        }

        default:
        {
            return nullptr;
        }
    }  

    return NemMemPointer;
}