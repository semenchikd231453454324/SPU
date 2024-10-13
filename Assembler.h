#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "SFUStruct.h"

#define OneCellCommand(commandname, commandEnum)                \
    if(strcmp(CurrentCommand, commandname))                     \
        {                                                       \
            Commands->code[Commands->codeSize] = commandEnum;   \
                                                                \
            Commands->codeSize = Commands->codeSize + 1;        \
        }                                                       \

#define OneCellCommandOut(commandEnum, commandname)                         \
    case commandEnum:                                                       \
    {                                                                       \
        fprintf(CommmandsTextout, commandname "\n");                        \
                                                                            \
        ip += 1;                                                            \
                                                                            \
        break;                                                              \
    }
    
struct AsmStruct
{

    size_t LinesCounter, TextSize;

    char* CommandsTextBuffer;
};


int Assembler(SFUStruct* Commands, AsmStruct* TextStruct);
int disAssembler(SFUStruct* Commands, AsmStruct* TextStruct);

#endif