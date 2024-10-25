#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#define TEXT_NAME "commands.txt"
#include "Assembler.h"
#include "AsmStructFuncs.h"

int AsmStructCtor(AsmStruct* TextData)
{
    assert(TextData);

    FILE *MoyText = fopen(TEXT_NAME, "r");
    if (!MoyText)
    {
        printf("pointer moytext failure");
        return 1;
    }

    struct stat FileInf = {};
    stat(TEXT_NAME, &FileInf);

    TextData->TextSize = FileInf.st_size;

    TextData->CommandsTextBuffer = (char*) calloc(TextData->TextSize, sizeof(char));
    if (!TextData->CommandsTextBuffer)
    {
        printf("pointer textdata failure");
        return 0;
    }

    fread(TextData->CommandsTextBuffer, sizeof(char), TextData->TextSize, MoyText);

    // for(size_t i = 0; i < TextData->TextSize; i++)
    // {
    //     printf("%c", TextData->CommandsTextBuffer[i]);
    // }

    for(size_t i = 0; i < TextData->TextSize; i++)                
    {
        if(TextData->CommandsTextBuffer[i] == '\n')
        {
            TextData->LinesCounter++;
        }
    }
    
    TextData->LinesCounter+=1;

    TextData->CommandsLinePointers = (char**) calloc(TextData->LinesCounter, sizeof(char*));

    char* CurrentLinePointer = TextData->CommandsTextBuffer;
    int CurrentTextDataNum = 0, CurrentElemInLineNumber = 0;


    for(size_t i = 0; i < TextData->LinesCounter; i++)            //TODO ask why    
    {   
        TextData->CommandsLinePointers[i] = CurrentLinePointer;

        CurrentElemInLineNumber = 0;

        while(TextData->CommandsTextBuffer[CurrentTextDataNum] != '\n' && TextData->CommandsTextBuffer[CurrentTextDataNum])
        {
            CurrentTextDataNum++;
            CurrentElemInLineNumber++;
        }

        TextData->CommandsTextBuffer[CurrentTextDataNum] = '\0';
        CurrentElemInLineNumber++;
        CurrentTextDataNum++;
        CurrentLinePointer = CurrentLinePointer + CurrentElemInLineNumber;
    }

    return 0;  //FIXME
}

int AsmStructDtor(AsmStruct* TextData)
{
    assert(TextData);

    free(TextData->CommandsTextBuffer);
    free(TextData->CommandsLinePointers);

    TextData = {};

    return 0;
}