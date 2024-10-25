#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "../include/SFUStruct.h"
#include "../include/SFUStructFuncs.h"


int SFUStructCtor(SFUStruct* Commands)
{
    assert(Commands);

    Commands->code = (int*) calloc(ConstCommandsSize, sizeof(int));
    Commands->registers = (int*) calloc(RegisterQuantity, sizeof(int));
    Commands->Labels = (LabelStrruct*) calloc(LabelsQuantity, sizeof(LabelStrruct));

    Commands->codeSize = 0;
    Commands->CurrentLabelsQuantity = 0;

    return 0;
}

int SFUStructDtor(SFUStruct* Commands)      //TODO ask where to use
{
    assert(Commands);

    free(Commands->code);
    free(Commands->registers);
    free(Commands->Labels);
    
    Commands = {};

    return 0;
}