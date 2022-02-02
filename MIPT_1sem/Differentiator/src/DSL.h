//
// Created by mikhalinho on 26.11.2021.
//

#ifndef DIFFERENTIATOR_DSL_H
#define DIFFERENTIATOR_DSL_H


enum types {
    EMPTY       = 0,
    DIGITAL     = 1,
    VARIABLE    = 2,
    U_OPERATOR  = 3,
    B_OPERATOR  = 4,
};


enum Operators {
    ADD         = 43,
    SUB         = 45,
    MUL         = 42,
    DIV         = 47,
    MOD         = 37,
    POW         = 94,
    ABS         = 97,
    SIN         = 115,
    COS         = 99,
    LN          = 108,

};

enum {
    EQUAL_ZERO      = 0,
    EQUAL_ONE       = 1,
    TWO_DIGITALS    = 2,

    NOTHING         ,
};

enum direction {
    LEFT        = 0,
    RIGHT       = 1,
};

#define ZERO Create_node(DIGITAL, 0)
#define C Create_node(DIGITAL, 1)
#define CONST(NUM) Create_node(DIGITAL, NUM)

#define L copy_subtree(node->left)
#define R copy_subtree(node->right)

#define ISLZERO if (node->left->type == DIGITAL && node->left->data.digit == 0)
#define ISRZERO if (node->right->type == DIGITAL && node->right->data.digit == 0)
#define ISDIGDIG if (node->left->type == DIGITAL && node->right->type == DIGITAL)

#define LONE node->left->type == DIGITAL && node->left->data.digit == 1
#define VARVAR node->right->type == VARIABLE && node->left->type == VARIABLE
#define RONE node->right->type == DIGITAL && node->right->data.digit == 1
#define RZERO node->right->type == DIGITAL && node->right->data.digit == 0

#define LL node->left->left
#define LR node->left->right
#define RL node->right->left
#define RR node->right->right

#define OPER node->data.oper
#define DIG node->data.digit
#define VAR node->data.variable

#define RDEC Create_node(B_OPERATOR, SUB, copy_subtree(node->right), C)

#define RSQR Create_node(B_OPERATOR, POW, node->right, CONST(2))

#define dL _differentiate(node->left)
#define dR _differentiate(node->right)

#define dADD Create_node(B_OPERATOR, ADD, dL, dR)
#define dSUB Create_node(B_OPERATOR, SUB, dL, dR)

#define LdR Create_node(B_OPERATOR, MUL, L, dR)
#define RdL Create_node(B_OPERATOR, MUL, dL, R)

#define dMUL Create_node(B_OPERATOR, ADD, LdR, RdL)
#define dNMUL Create_node(B_OPERATOR, SUB, RdL, LdR)
#define dDIV Create_node(B_OPERATOR, DIV, dNMUL, RSQR)
#define dCDIV Create_node(B_OPERATOR, SUB, ZERO, Create_node(B_OPERATOR, DIV, dR, RSQR))

#define COSL Create_node(U_OPERATOR, COS, L)
#define SINL Create_node(U_OPERATOR, SIN, L)
#define NSINL Create_node(B_OPERATOR, SUB, ZERO, SINL)

#define dSIN Create_node(B_OPERATOR, MUL, dL, COSL)
#define dCOS Create_node(B_OPERATOR, MUL, dL, NSINL)

#define dLOG Create_node(B_OPERATOR, DIV, dL, L)

#define dVPC Create_node(B_OPERATOR, MUL, R, Create_node(B_OPERATOR, MUL, dL,       \
                                             Create_node(B_OPERATOR, POW, L, RDEC)))

#define dCPV Create_node(B_OPERATOR, MUL, copy_subtree(node), Create_node(B_OPERATOR, MUL, dR, \
                                            Create_node(U_OPERATOR, LN, L)))

#define dVPV Create_node(B_OPERATOR, MUL, copy_subtree(node), Create_node(B_OPERATOR, ADD,              \
                                                              Create_node(B_OPERATOR, MUL, dR,          \
                                                              Create_node(U_OPERATOR, LN, L)),          \
                                                              Create_node(B_OPERATOR, DIV,              \
                                                              Create_node(B_OPERATOR, MUL, dL, R), L)))
#endif //DIFFERENTIATOR_DSL_H
