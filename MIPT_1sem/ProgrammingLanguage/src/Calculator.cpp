//
// Created by mikhalinho on 29.11.2021.
//

#include "Calculator.h"



int Calculator::GetLine(const char *str) {
    equation_str = str;

    int value = GetExpression();

    if (Require('$')) return SYNTAX_ERROR;
    else return value;
}

int Calculator::Require(char c) {
    if (*equation_str == c) equation_str++;
    else return SYNTAX_ERROR;

    return ALL_OK;
}

int Calculator::GetNumber() {
    int value = 0;

    const char* copy_str = equation_str;

    while ('0' <= *equation_str && *equation_str <= '9') {
        value = value * 10 + (*equation_str - '0');
        equation_str++;
    }
    if (copy_str == equation_str) return SYNTAX_ERROR;

    return value;
}

int Calculator::GetExpression() {
    int lhs = GetMDop();
    if (lhs == SYNTAX_ERROR) return SYNTAX_ERROR;

    while (*equation_str == '+' || *equation_str == '-') {
        char oper = *equation_str;
        equation_str++;

        int rhs = GetMDop();
        if (rhs < 0) return rhs;

        if (oper == '+')    lhs += rhs;
        else                lhs -= rhs;
    }

    return lhs;
}


int Calculator::GetMDop() {
    int lhs = GetPow();
    if (lhs == SYNTAX_ERROR) return SYNTAX_ERROR;

    while (*equation_str == '*' || *equation_str == '/') {
        char oper = *equation_str;
        equation_str++;

        int rhs = GetPow();
        if (rhs == SYNTAX_ERROR) return SYNTAX_ERROR;

        if (oper == '*')    lhs *= rhs;
        else                lhs /= rhs;
    }

    return lhs;
}


int Calculator::GetPow() {
    int lhs = GetBrackets();
    if (lhs == SYNTAX_ERROR) return SYNTAX_ERROR;

    while (*equation_str == '^') {
        equation_str++;

        int rhs = GetBrackets();
        if (rhs == SYNTAX_ERROR) return SYNTAX_ERROR;

        lhs = (int) pow(lhs, rhs);
    }

    return lhs;
}

int Calculator::GetBrackets() {
    if (*equation_str == '(') {
        equation_str++;
        int lhs = GetExpression();

        if (Require(')')) return SYNTAX_ERROR;
        else return lhs;
    } else
        return GetNumber();
}