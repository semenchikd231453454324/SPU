#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "Stack.h"
#include "SFUStruct.h"
#include "Run.h"


void Run(SFUStruct* Commands)
{
    assert(Commands);

    StackStruct Stack = {};
    StackCtor(&Stack);

    int ip = 0;
    int True = 1;       //TODO rename workstatus

    while (True)
    {
        switch (Commands->code[ip])
        {
        case push:                                             //Кладем в стэк
        {                                             
            StackPush(&Stack, Commands->code[ip + 1]);
            ip = ip + 2;

            break;
        }

        case pop:                                             //Достаем из стэка
        {
            StackPop(&Stack);

            ip = ip + 1;

            break;
        }

        case in:                                               //Кладем в стэк + ввод с клавы
        {
            int PushValue = 0;

            printf("Enter new Stack element\n");
            scanf("%d", &PushValue);

            StackPush(&Stack, PushValue);

            ip = ip + 1;

            break;
        }                                             

        case out:                                             //Достаем из стэка + печатаем
        {
            int PopValue = 0;

            PopValue = StackPop(&Stack);

            printf("Upper Stack element = %d", PopValue);

            ip = ip + 1;
        }

        case add:                                             //Cложение двух верхних элементов
        {
            int FirstTerm = 0, SecondTerm = 0, Result = 0;
            FirstTerm  = StackPop(&Stack);
            SecondTerm = StackPop(&Stack);

            Result = FirstTerm + SecondTerm;

            StackPush(&Stack, Result);

            ip = ip + 1;

            break;
        }

        case subtr:                                              //Вычитание двух верхних элементов(верхний это вычитаемое)
        {
            int Minued = 0, Subtrahend = 0, Result = 0;

            Subtrahend = StackPop(&Stack);
            Minued     = StackPop(&Stack);

            Result = Minued - Subtrahend;

            StackPush(&Stack, Result);

            ip = ip + 1;

            break;
        }

        case multipl:                                             //Умножение
        {
            int FirstFactor = 0, SecondFactor = 0, Result = 0;

            FirstFactor  = StackPop(&Stack);
            SecondFactor = StackPop(&Stack);

            Result = FirstFactor - SecondFactor;

            StackPush(&Stack, Result);

            ip = ip + 1;

            break;
        }

        case div:                                             //Деление
        {
            int Dividend = 0, Divider = 0, Result = 0;

            Divider  = StackPop(&Stack);
            Dividend = StackPop(&Stack);

            Result = Dividend / Divider;

            StackPush(&Stack, Result);

            ip = ip + 1;

            break;
        }

        case SQRT:                                             //sqrt
        {
            int TemporaryBuf = 0;

            TemporaryBuf = StackPop(&Stack);

            StackPush(&Stack, sqrt(TemporaryBuf));

            ip = ip + 1;

            break;
        }

        case SIN:                                               //sin
        {
            StackPush(&Stack, (int) sin(StackPop(&Stack)));

            ip = ip + 1;

            break;
        }

        case COS:                                               //cos
        {
            StackPush(&Stack, (int) cos(StackPop(&Stack)));

            ip = ip + 1;

            break;
        }

        case dump:                                              //dump
        {
            DUMP(&Stack);

            ip = ip + 1;

            break;
        }

        case hlt:                                               //hlt
        {
            True = 0;

            ip = ip + 1;

            break;
        }

        default:
        {
            printf("Syntax error, entered Invalid command\n");

            True = 0;

            break;
        }
        }
    }
    

}