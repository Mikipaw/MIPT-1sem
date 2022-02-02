//
// Created by mikhalinho on 08.12.2021.
//

#ifndef PROGRAMMINGLANGUAGE_ENUMS_H
#define PROGRAMMINGLANGUAGE_ENUMS_H


enum AnalyzerEnums {
    EMPTY_LINE          = 10,
    ZERO                = 0,
    EXPRESSION          = 1,
    FUNCTION            = 6,
    VARIABLE            = 2,
    INITIALISING        = 31,
    ASSIGNMENT          = 22,
    CALL                = 3,
    STATEMENT           = 4,
    WHILE               = 32,
    IF                  = 33,
    IFELSE              = 77,
    DEFINE              = 34,
    END                 = 38,
    STOP                = 99,
    MAINE               = 30,
    SCAN                = 36,
    PRINT               = 35,
    RAD                 = 37,

};

//maybe
//trying
enum types {
    EMPTY       = 0,
    DIGITAL     = 1,
    VARI        = 2,
    U_OPERATOR  = 3,
    B_OPERATOR  = 4,
    STAT        = 5,

};


enum Operators {
    ADD         = 43,
    SUB         = 45,
    MUL         = 42,
    DIV         = 47,
    //MOD         = 37,
    POW         = 94,
    ABS         = 97,
    SIN         = 115,
    COS         = 99,
    LN          = 108,
    ASS         = 61,
    DEF         = 35,
    FUNC        = 102,
    ST          = 123,
    EQUALITY    = 61,


};

enum direction {
    LEFT        = 0,
    RIGHT       = 1,
};

#define OPER node->data.oper
#define DIG node->data.digit
#define VAR node->data.variable

#define L copy_subtree(node->left)
#define R copy_subtree(node->right)


#define LL node->left->left
#define LR node->left->right
#define RL node->right->left
#define RR node->right->right

#endif //PROGRAMMINGLANGUAGE_ENUMS_H
