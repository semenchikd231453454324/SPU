#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "SFUStruct.h"
#include "..\Stack\include\StackFuncs.h"
#include "..\include\Assembler.h"
#include "..\include\Run.h"

int main()
{
    SFUStruct Commands = {};
    AsmStruct TextStruct = {};

    Assembler(&Commands, &TextStruct);

    for(size_t i = 0; i < 30; i++)
    {
        printf("code[%d] = %d\n", i, Commands.code[i]);
    }
    // StackStruct Stack = {};
    // StackCtor(&Stack);

    // StackPush(&Stack, 6);
    // StackPush(&Stack, 7);
    // StackPush(&Stack, 8);
    // DUMP(&Stack);

    // StackPopprint;
    // StackPopprint;

    // VERIF(&Stack);

    // DUMP(&Stack);
    Run(&Commands);

}
//TODO labels  dump 