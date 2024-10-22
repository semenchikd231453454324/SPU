#ifndef SFUSTRUCT_H
#define SFUSTRUCT_H

#include <stdlib.h>

enum ComandsValue {myau, Instruction_push, Instruction_pop, Instruction_in, Instruction_out,  Instruction_add, Instruction_subtr, Instruction_multipl, Instruction_div, Instruction_SQRT, Instruction_SIN, Instruction_COS, Instruction_dump, Instruction_hlt, Instruction_jmp, Instruction_ja, Instruction_jae, Instruction_jb, Instruction_jbe, Instruction_je, Instruction_jne, Instruction_pushR, Instruction_popR};
enum RegistersName {ax, bx, cx, dx, ex, fx, gx, hx, ix, jx};

#define RegisterQuantity 10

struct SFUStruct
{
    int* code;
    size_t codeSize;

    int* registers;
};


#endif