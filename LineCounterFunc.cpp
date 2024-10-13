#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#define TEXT_NAME "commands.txt"
#include "Assembler.h"
#include "LineCounterFunc.h"

int LineCounterFunc(AsmStruct* TextData)
{
    FILE *MoyText = fopen(TEXT_NAME, "r");
    if (!MoyText)
    {
        printf("pointer moytext failure");
        return 1;
    }

    struct stat FileInf = {};
    stat(TEXT_NAME, &FileInf);

    TextData->TextSize = FileInf.st_size;

    char* Data = (char*) calloc(TextData->TextSize, sizeof(char));
    if (!Data)
    {
        printf("pointer textdata failure");
        return 0;
    }

    fread(Data, sizeof(char), TextData->TextSize, MoyText);

    for(size_t i = 0; i < TextData->TextSize; i++)                
    {
        if(Data[i] == '\n')
        {
            TextData->LinesCounter++;
        }
    }

    return 0;  //FIXME
}

