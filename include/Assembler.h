#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "SFUStruct.h"


struct AsmStruct
{
    size_t LinesCounter, TextSize;

    char* CommandsTextBuffer;

    char** CommandsLinePointers;
};


int Assembler(SFUStruct* Commands, AsmStruct* TextStruct);
int disAssembler(SFUStruct* Commands, AsmStruct* TextStruct);

#endif