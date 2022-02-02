//
// Created by mikipaw on 16.10.2020.
//

#define DO_PUSH {                                   \
integ = (int) array[++i];                           \
if(integ == 0){                                     \
    second = array[++i];                            \
    cpu_stack.push(second);                         \
    }                                               \
    else if (integ < 5){                            \
        cpu_stack.push(reg[integ-1]);               \
    }                                               \
    else {                                          \
        second = array[++i];                        \
        if (second < 1200 && second > 4) return UNAVAILABLE_RAM;  \
        cpu_stack.push(RAM[(int)second]);           \
    }                                               \
};                                                  \

#define DO_POP {                                        \
integ = (int) array[++i];                               \
if(integ == 0) cpu_stack.pop();                         \
else if (integ == 5) {                                  \
    second = array[++i];                                \
    if (second < 1200 && second > 4) return UNAVAILABLE_RAM;  \
    if(second <= 4) cpu_stack.pop(&RAM[(int)reg[(int)second - 1]]);\
    else cpu_stack.pop(&RAM[(int)second]);              \
}                                                       \
else cpu_stack.pop(&reg[integ-1]);                      \
};                                                      \

#define DO_ADD {                    \
if(cpu_stack.Get_Size() < 2)        \
{                                   \
Stack_info(cpu_stack);              \
    return EMPTY_STACK;             \
}                                   \
cpu_stack.pop(&first);              \
cpu_stack.pop(&second);             \
cpu_stack.push(first + second);     \
};                                  \

#define DO_SUB {                    \
if(cpu_stack.Get_Size() < 2)        \
    return EMPTY_STACK;             \
cpu_stack.pop(&first);              \
cpu_stack.pop(&second);             \
cpu_stack.push(second - first);     \
};                                  \

#define DO_MUL {                    \
if(cpu_stack.Get_Size() < 2)        \
    return EMPTY_STACK;             \
cpu_stack.pop(&first);              \
cpu_stack.pop(&second);             \
cpu_stack.push(first * second);     \
};                                  \

#define DO_DIV {                    \
if(cpu_stack.Get_Size() < 2)        \
    return EMPTY_STACK;             \
cpu_stack.pop(&first);              \
cpu_stack.pop(&second);             \
cpu_stack.push(second / first);     \
};                                  \

#define DO_NEG {                    \
cpu_stack.pop(&first);              \
cpu_stack.push(-first);             \
};                                  \

#define DO_SINUS {                  \
cpu_stack.pop(&first);              \
cpu_stack.push(sin(3.14 * first / 180));\
};                                  \

#define DO_COS {                    \
cpu_stack.pop(&first);              \
cpu_stack.push(cos(3.14 * first / 180));\
};                                  \

#define DO_SQRT {                   \
cpu_stack.pop(&first);              \
if(first < 0)                       \
    return NEGATIVE_RADICAL;        \
cpu_stack.push(sqrt(first));        \
};                                  \

#define DO_POW {                    \
cpu_stack.pop(&first);              \
cpu_stack.pop(&second);             \
cpu_stack.push(pow(first, second)); \
};                                  \

#define DO_IN {                     \
printf("\nInput: \n");              \
scanf("%lf", &first);               \
cpu_stack.push(first);              \
};                                  \

#define DO_OUT {                    \
cpu_stack.pop(&first);              \
printf("\nOutput: %lf\n", first);   \
};                                  \

#define DO_DUMP {                   \
CPU_info(*this);                    \
Stack_info(cpu_stack);              \
};                                  \

#define DO_HLT {                    \
printf("\nProcess finishing...\n"); \
return ALL_OK;                      \
};                                  \

#define DO_JMP {                    \
integ = (int) (array[++i]);         \
i     = integ - 1;                  \
};                                  \
//if(num == 23) Change_ret(i + 1);    \


#define DO_JA {                             \
integ = (int) array[++i];                   \
if(cpu_stack.Get_Size() < 2)                \
    return EMPTY_STACK;                     \
cpu_stack.pop(&first);                      \
cpu_stack.pop(&second);                     \
if(second > first) {                        \
i = integ - 1;                              \
}                                           \
};                                          \

#define DO_JAE {                        \
integ = (int) array[++i];               \
if(cpu_stack.Get_Size() < 2)            \
    return EMPTY_STACK;                 \
cpu_stack.pop(&first);                  \
cpu_stack.pop(&second);                 \
if(second >= first) {                   \
i = integ - 1;                          \
}                                       \
};                                      \

#define DO_JB {                         \
integ = (int) array[++i];               \
if(cpu_stack.Get_Size() < 2)            \
    return EMPTY_STACK;                 \
cpu_stack.pop(&first);                  \
cpu_stack.pop(&second);                 \
if(second < first) {                    \
i = integ - 1;                          \
}                                       \
};                                      \

#define DO_JBE {                        \
integ = (int) array[++i];               \
if(cpu_stack.Get_Size() < 2)            \
    return EMPTY_STACK;                 \
cpu_stack.pop(&first);                  \
cpu_stack.pop(&second);                 \
if(second <= first) {                   \
i = integ - 1;                          \
}                                       \
};                                      \

#define DO_JE {                         \
integ = (int) array[++i];               \
if(cpu_stack.Get_Size() < 2)            \
    return EMPTY_STACK;                 \
cpu_stack.pop(&first);                  \
cpu_stack.pop(&second);                 \
if(abs(second - first) < 10e-5) {       \
i = integ - 1;                          \
}                                       \
};                                      \

#define DO_JNE {                        \
integ = (int) array[++i];               \
if(cpu_stack.Get_Size() < 2)            \
    return EMPTY_STACK;                 \
cpu_stack.pop(&first);                  \
cpu_stack.pop(&second);                 \
if(second != first) {                   \
i = integ - 1;                          \
}                                       \
};                                      \

#define DO_MOD {                                \
if(cpu_stack.Get_Size() < 2)                    \
    return EMPTY_STACK;                         \
cpu_stack.pop(&first);                          \
cpu_stack.pop(&second);                         \
cpu_stack.push((int)second % (int)first);       \
};                                              \

#define DO_INT {                                \
cpu_stack.pop(&first);                          \
first = (double) (int) first;                   \
cpu_stack.push(first);                          \
};                                              \


/*
#define DO_DRAW {                                   \
Draw();                                       \
};
*/
#define DO_IDIV {                           \
if(cpu_stack.Get_Size() < 2)                \
    return EMPTY_STACK;                     \
cpu_stack.pop(&first);                      \
cpu_stack.pop(&second);                     \
cpu_stack.push((int)second / (int)first);   \
};                                          \

//TODO: function names.
/*
#define DO_RET {                        \
i = cpu_stack.Get_ret() - 1;            \
};
*/

DEF_CMD( PUSH,  40,    {DO_PUSH}, 320)
DEF_CMD( POP,   20,   {DO_POP},  239)
DEF_CMD( ADD,   0,    {DO_ADD},  201)
DEF_CMD( SUB,   1,    {DO_SUB},  234)
DEF_CMD( MUL,   2,    {DO_MUL},  238)
DEF_CMD( DIV,   3,    {DO_DIV},  227)
DEF_CMD( NEG,   4,    {DO_NEG},  218)
DEF_CMD( SINUS, 5,    {DO_SINUS},402)
DEF_CMD( COS,   6,    {DO_COS},  229)
DEF_CMD( SQRT,  7,    {DO_SQRT}, 330)
DEF_CMD( POW,   8,    {DO_POW},  246)
DEF_CMD( IN,    9,    {DO_IN},   151)
DEF_CMD( OUT,   10,   {DO_OUT},  248)
DEF_CMD( DUMP,  11,   {DO_DUMP}, 310)
DEF_CMD( HLT,   12,   {DO_HLT},  232)
DEF_CMD( JMP,   21,   {DO_JMP},  231)
DEF_CMD( JA ,   22,   {DO_JA},   139)
DEF_CMD( JAE,   23,   {DO_JAE},  208)
DEF_CMD( JB ,   24,   {DO_JB},   140)
DEF_CMD( JBE,   25,   {DO_JBE},  209)
DEF_CMD( JE ,   26,   {DO_JE},   143)
DEF_CMD( JNE,   27,   {DO_JNE},  221)
DEF_CMD( MOD,   13,   {DO_MOD},  224)
DEF_CMD( IDIV,  14,   {DO_IDIV}, 300)
DEF_CMD( INT,   15,   {DO_INT},  235)
//DEF_CMD( DRAW,  15,   {DO_DRAW}, 302)
/*
DEF_CMD( RET,   22,   {DO_RET})
DEF_CMD( CAL,   23,   {DO_JMP})
*/