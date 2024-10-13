#ifndef SFUSTRUCT_H
#define SFUSTRUCT_H

#include <stdlib.h>

enum ComandsValue {myau, push, pop, in, out,  add, subtr, multipl, div, SQRT, SIN, COS, dump, hlt};

struct SFUStruct
{
    int* code;
    size_t codeSize;
};


#endif