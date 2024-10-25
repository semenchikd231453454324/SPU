#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "SFUStruct.h"
#include "Assembler.h"
#include "AsmStructFuncs.h"
#include "../include/SFUStructFuncs.h"


#define TEXT_NAME "commands.txt"

int Assembler(SFUStruct* Commands, AsmStruct* TextStruct)
{
    assert(Commands);
    assert(TextStruct);

    #define NumSearch strchr(TextStruct->CommandsLinePointers[LineNum], '0') || strchr(TextStruct->CommandsLinePointers[LineNum], '1') || strchr(TextStruct->CommandsLinePointers[LineNum], '2') || strchr(TextStruct->CommandsLinePointers[LineNum], '3') || strchr(TextStruct->CommandsLinePointers[LineNum], '4') || strchr(TextStruct->CommandsLinePointers[LineNum], '5') || strchr(TextStruct->CommandsLinePointers[LineNum], '6') || strchr(TextStruct->CommandsLinePointers[LineNum], '7') || strchr(TextStruct->CommandsLinePointers[LineNum], '8') || strchr(TextStruct->CommandsLinePointers[LineNum], '9')

    #define OneCellCommand(commandname, commandEnum)            \
    if(!strcmp(CurrentCommand, commandname))                    \
        {                                                       \
            Commands->code[Commands->codeSize] = commandEnum;   \
                                                                \
            Commands->codeSize = Commands->codeSize + 1;        \
        }                                                       \


    #define JumpCommand(commandname, commandEnum)                                                               \
    if(!strcmp(CurrentCommand, commandname))                                                                    \
        {                                                                                                       \
            Commands->code[Commands->codeSize] = commandEnum;                                                   \
                                                                                                                \
            if (NumSearch)                                                                                      \
            {                                                                                                   \
                int ValueForCommand = 0;                                                                        \
                sscanf(TextStruct->CommandsLinePointers[LineNum] + strlen(commandname),"%s", CurrentCommand);   \
                                                                                                                \
                ValueForCommand = atoi(CurrentCommand);                                                         \
                                                                                                                \
                Commands->code[Commands->codeSize + 1] = ValueForCommand;                                       \
            }                                                                                                   \
            else                                                                                                \
            {                                                                                                   \
                sscanf(TextStruct->CommandsLinePointers[LineNum] + strlen(commandname),"%s", CurrentCommand);   \
                                                                                                                \
                for (int i = 0; i < Commands->CurrentLabelsQuantity; i++)                                       \
                {                                                                                               \
                    if (!strcmp(Commands->Labels[i].CurrentLabelName, CurrentCommand))                          \
                    {                                                                                           \
                        Commands->code[Commands->codeSize + 1] = Commands->Labels[i].LabelIp;                   \
                                                                                                                \
                        i = Commands->CurrentLabelsQuantity;                                                    \
                    }                                                                                           \
                }                                                                                               \
            }                                                                                                   \
                                                                                                                \
            Commands->codeSize = Commands->codeSize + 2;                                                        \
        }
    

    FILE* CommmandsText = fopen(TEXT_NAME, "r");
    if(!CommmandsText)
    {
        printf("pointer CommmandsText failure");
        return 1;
    }

    AsmStructCtor(TextStruct);

    //printf("%d", TextStruct->TextSize);

    // for(size_t i = 0; i < TextStruct->TextSize; i++)
    // {
    //     printf("%c", TextStruct->CommandsTextBuffer[i]);
    // }

    SFUStructCtor(Commands);

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
        else OneCellCommand("stkdump", Instruction_stkdump)
        else OneCellCommand("sfudump", Instruction_sfudump)
        else OneCellCommand("lbldump", Instruction_lbldump)
        else OneCellCommand("hlt", Instruction_hlt)
        else JumpCommand("jmp", Instruction_jmp)
        else JumpCommand("ja", Instruction_ja)
        else JumpCommand("jae", Instruction_jae)
        else JumpCommand("jb", Instruction_jb)
        else JumpCommand("jbe", Instruction_jbe)
        else JumpCommand("je", Instruction_je)
        else JumpCommand("jne", Instruction_jne)
        else if(strchr(CurrentCommand, ':'))
        {
            int i = 0;                                      //TODO массив структур что и как???

            char TemporraryBuf [15] ={};

            while (CurrentCommand[i] != ':')
            {
                TemporraryBuf[i] = CurrentCommand[i];

                i++;
            }
            
            i++;

            TemporraryBuf[i] = '\0';

            (Commands->Labels[Commands->CurrentLabelsQuantity]).LabelIp = Commands->codeSize;     //эээ сомнительно

            for(int j = 0; j < i; j++)
            {
                (Commands->Labels[Commands->CurrentLabelsQuantity]).CurrentLabelName[j] = TemporraryBuf[j];             //TODO норм ли?
            }
         
            Commands->CurrentLabelsQuantity++;
        }


        else
        {
            printf("Assembler doesn't know this command\n");

            return 0;
        }
        
    }   

    FILE* Binary = fopen("Binary.hui", "wb");

    fwrite(Commands->code, sizeof(int), Commands->codeSize, Binary);

    fclose(Binary);
    fclose(CommmandsText);

    #undef OneCellCommand
    #undef JumpCommand

    return 0;
}

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

    #define JumpCommandOut(commandEnum, commandname)                            \
    case commandEnum:                                                           \
    {                                                                           \
        fprintf(CommmandsTextout, commandname " %d\n", Commands->code[ip + 1]); \
                                                                                \
        ip = ip + 2;                                                            \
                                                                                \
        break;                                                                  \
    }   

    size_t ip = 0;

    for(size_t LineNum = 0; LineNum < (TextStruct->LinesCounter - Commands->CurrentLabelsQuantity); LineNum++)
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
            OneCellCommandOut(Instruction_stkdump, "stkdump")
            OneCellCommandOut(Instruction_sfudump, "sfudump")
            OneCellCommandOut(Instruction_lbldump, "lbldump")
            OneCellCommandOut(Instruction_hlt, "hlt")
            JumpCommandOut(Instruction_jmp, "jmp")
            JumpCommandOut(Instruction_ja, "ja")
            JumpCommandOut(Instruction_jae, "jae")
            JumpCommandOut(Instruction_jb, "jb")
            JumpCommandOut(Instruction_jbe, "jbe")
            JumpCommandOut(Instruction_je, "je")
            JumpCommandOut(Instruction_jne, "jne")

            default:
            {
                fprintf(CommmandsTextout, "unknown instruction %d\n", Commands->code[ip]);
                
                LineNum = TextStruct->LinesCounter;

                break;
            }
        }
    }

    #undef OneCellCommandOut
    #undef JumpCommandOut

    AsmStructDtor(TextStruct);

    return 0;
}