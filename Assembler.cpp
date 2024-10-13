#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "SFUStruct.h"
#include "Assembler.h"
#include "LineCounterFunc.h"

#define TEXT_NAME "commands.txt"
#define ConstCommandsSize 20

int Assembler(SFUStruct* Commands, AsmStruct* TextStruct)
{
    assert(Commands);
    assert(TextStruct);

    FILE* CommmandsText = fopen(TEXT_NAME, "r");
    if(!CommmandsText)
    {
        printf("pointer CommmandsText failure");
        return 1;
    }
    size_t CommandsSize = LineCounterFunc(TextStruct);          //FIXME

    Commands->code = (int*) calloc(ConstCommandsSize, sizeof(int));         //TODO заменить количество константное на нормальное

    char CurrentCommand [20] = {};

    for(size_t LineNum = 0; LineNum < TextStruct->LinesCounter; LineNum++)
    {
        CurrentCommand [20] = {};

        fscanf(CommmandsText,"%s", CurrentCommand);         //TODO read about sscanf

        if(strcmp(CurrentCommand, "push"))
        {
            Commands->code[Commands->codeSize] = push;

            int ValueForCommand = 0;
            fscanf(CommmandsText,"%d", ValueForCommand);

            Commands->code[Commands->codeSize + 1] = ValueForCommand;

            Commands->codeSize = Commands->codeSize + 2;
        }
        else OneCellCommand("pop", pop)
        else OneCellCommand("in", in)
        else OneCellCommand("out", out)
        else OneCellCommand("add", add)
        else OneCellCommand("subtr", subtr)
        else OneCellCommand("multipl", multipl)
        else OneCellCommand("div", div)
        else OneCellCommand("SQRT", SQRT)
        else OneCellCommand("SIN", SIN)
        else OneCellCommand("COS", COS)
        else OneCellCommand("dump", dump)
        else OneCellCommand("hlt", hlt)
    }   

    fclose(CommmandsText);
}

int disAssembler(SFUStruct* Commands, AsmStruct* TextStruct)
{
    assert(Commands);
    assert(TextStruct);

    FILE* CommmandsTextout = fopen("commandsout.txt", "rw");
    if(!CommmandsTextout)
    {
        printf("pointer CommmandsText failure");
        return 1;
    }

    size_t ip = 0;

    for(size_t LineNum = 0; LineNum < TextStruct->LinesCounter; LineNum++)
    {
        switch (Commands->code[ip])
        {
            case push:
            {
                fprintf(CommmandsTextout, "push %d\n", Commands->code[ip + 1]);

                ip += 2;
        
                break;
            }
            OneCellCommandOut(pop, "pop")
            OneCellCommandOut(in, "in")
            OneCellCommandOut(out, "out")
            OneCellCommandOut(add, "add")
            OneCellCommandOut(subtr, "subtr")
            OneCellCommandOut(multipl, "multipl")
            OneCellCommandOut(div, "div")
            OneCellCommandOut(SQRT, "SQRT")
            OneCellCommandOut(SIN, "SIN")
            OneCellCommandOut(COS, "COS")
            OneCellCommandOut(dump, "dump")
            OneCellCommandOut(hlt, "hlt")

            default:
            {
                fprintf(CommmandsTextout, "unknown instruction %d\n", Commands->code[ip]);
                
                LineNum = TextStruct->LinesCounter;

                break;
            }
        }
    }
}