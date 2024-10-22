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
#define ConstCommandsSize 30

int Assembler(SFUStruct* Commands, AsmStruct* TextStruct)
{
    assert(Commands);
    assert(TextStruct);

    #define OneCellCommand(commandname, commandEnum)            \
    if(!strcmp(CurrentCommand, commandname))                    \
        {                                                       \
            Commands->code[Commands->codeSize] = commandEnum;   \
                                                                \
            Commands->codeSize = Commands->codeSize + 1;        \
        }                                                       \


    #define TwoCellCommand(commandname, commandEnum)                                                            \
    if(!strcmp(CurrentCommand, commandname))                                                                    \
        {                                                                                                       \
            Commands->code[Commands->codeSize] = commandEnum;                                                   \
                                                                                                                \
            int ValueForCommand = 0;                                                                            \
            sscanf(TextStruct->CommandsLinePointers[LineNum] + strlen(commandname),"%s", CurrentCommand);       \
                                                                                                                \
            ValueForCommand = atoi(CurrentCommand);                                                             \
                                                                                                                \
            Commands->code[Commands->codeSize + 1] = ValueForCommand;                                           \
                                                                                                                \
            Commands->codeSize = Commands->codeSize + 2;                                                        \
        }
    

    FILE* CommmandsText = fopen(TEXT_NAME, "r");
    if(!CommmandsText)
    {
        printf("pointer CommmandsText failure");
        return 1;
    }

    LineCounterFunc(TextStruct);          //FIXME

    //printf("%d", TextStruct->TextSize);

    // for(size_t i = 0; i < TextStruct->TextSize; i++)
    // {
    //     printf("%c", TextStruct->CommandsTextBuffer[i]);
    // }

    
    Commands->code = (int*) calloc(ConstCommandsSize, sizeof(int));         //TODO заменить количество константное на нормальное
    Commands->registers = (int*) calloc(RegisterQuantity, sizeof(int));

    char CurrentCommand [20] = {};

    for(size_t LineNum = 0; LineNum < TextStruct->LinesCounter; LineNum++)
    {
        CurrentCommand [20] = {};
        
        sscanf(TextStruct->CommandsLinePointers[LineNum], "%s", CurrentCommand);

        if(!strcmp(CurrentCommand, "push"))
        {
            Commands->code[Commands->codeSize] = Instruction_push;

            int ValueForCommand = 0;
            
            sscanf(TextStruct->CommandsLinePointers[LineNum] + 4, "%s", CurrentCommand);

            ValueForCommand = atoi(CurrentCommand);

            Commands->code[Commands->codeSize + 1] = ValueForCommand;

            Commands->codeSize = Commands->codeSize + 2;
        }
        else OneCellCommand("pop", Instruction_pop)
        else OneCellCommand("in", Instruction_in)
        else OneCellCommand("out", Instruction_out)
        else OneCellCommand("add", Instruction_add)
        else OneCellCommand("subtr", Instruction_subtr)
        else OneCellCommand("multipl", Instruction_multipl)
        else OneCellCommand("div", Instruction_div)
        else OneCellCommand("SQRT", Instruction_SQRT)
        else OneCellCommand("SIN", Instruction_SIN)
        else OneCellCommand("COS", Instruction_COS)
        else OneCellCommand("dump", Instruction_dump)
        else OneCellCommand("hlt", Instruction_hlt)
        else TwoCellCommand("jmp", Instruction_jmp)
        else TwoCellCommand("ja", Instruction_ja)
        else TwoCellCommand("jae", Instruction_jae)
        else TwoCellCommand("jb", Instruction_jb)
        else TwoCellCommand("jbe", Instruction_jbe)
        else TwoCellCommand("je", Instruction_je)
        else TwoCellCommand("jne", Instruction_jne)
        else TwoCellCommand("pushR", Instruction_pushR)
        else TwoCellCommand("popR", Instruction_popR)

        else
        {
            printf("Assembler doesn't know this command\n");

            return 0;
        }
        
    }   

    fclose(CommmandsText);

    #undef OneCellCommand
    #undef TwoCellCommand

    return 0;
}


                                                                //huihui

int disAssembler(SFUStruct* Commands, AsmStruct* TextStruct)
{
    assert(Commands);
    assert(TextStruct);

    FILE* CommmandsTextout = fopen("commandsout.txt", "w");  // FIXME
    if(!CommmandsTextout)
    {
        printf("pointer CommmandsText failure");
        return 1;
    }

    #define OneCellCommandOut(commandEnum, commandname)                     \
    case commandEnum:                                                       \
    {                                                                       \
        fprintf(CommmandsTextout, commandname "\n");                        \
                                                                            \
        ip += 1;                                                            \
                                                                            \
        break;                                                              \
    }

    #define TwoCellCommandOut(commandEnum, commandname)                         \
    case commandEnum:                                                           \
    {                                                                           \
        fprintf(CommmandsTextout, commandname " %d\n", Commands->code[ip + 1]); \
                                                                                \
        ip = ip + 2;                                                            \
                                                                                \
        break;                                                                  \
    }   

    size_t ip = 0;

    for(size_t LineNum = 0; LineNum < TextStruct->LinesCounter; LineNum++)
    {
        switch (Commands->code[ip])
        {
            case Instruction_push:
            {
                fprintf(CommmandsTextout, "push %d\n", Commands->code[ip + 1]);

                ip += 2;
        
                break;
            }
            OneCellCommandOut(Instruction_pop, "pop")
            OneCellCommandOut(Instruction_in, "in")
            OneCellCommandOut(Instruction_out, "out")
            OneCellCommandOut(Instruction_add, "add")
            OneCellCommandOut(Instruction_subtr, "subtr")
            OneCellCommandOut(Instruction_multipl, "multipl")
            OneCellCommandOut(Instruction_div, "div")
            OneCellCommandOut(Instruction_SQRT, "SQRT")
            OneCellCommandOut(Instruction_SIN, "SIN")
            OneCellCommandOut(Instruction_COS, "COS")
            OneCellCommandOut(Instruction_dump, "dump")
            OneCellCommandOut(Instruction_hlt, "hlt")
            TwoCellCommandOut(Instruction_jmp, "jmp")
            TwoCellCommandOut(Instruction_ja, "ja")
            TwoCellCommandOut(Instruction_jae, "jae")
            TwoCellCommandOut(Instruction_jb, "jb")
            TwoCellCommandOut(Instruction_jbe, "jbe")
            TwoCellCommandOut(Instruction_je, "je")
            TwoCellCommandOut(Instruction_jne, "jne")
            TwoCellCommandOut(Instruction_pushR, "pushR")
            TwoCellCommandOut(Instruction_popR, "popR")



            default:
            {
                fprintf(CommmandsTextout, "unknown instruction %d\n", Commands->code[ip]);
                
                LineNum = TextStruct->LinesCounter;

                break;
            }
        }
    }

    #undef OneCellCommandOut
    #undef TwoCellCommandOut

    return 0;
}