//
// Created by mikhalinho on 29.11.2021.
//

#ifndef PROGRAMMINGLANGUAGE_CALCULATOR_H
#define PROGRAMMINGLANGUAGE_CALCULATOR_H

#include <cmath>

#include "Error_codes.h"

class Calculator {

public:
    int GetLine(const char* str);


    int GetNumber();


    int GetExpression();


    int GetMDop();


    int GetBrackets();


    int GetPow();

private:


    int Require(char c);


    const char* equation_str = nullptr;
};


#endif //PROGRAMMINGLANGUAGE_CALCULATOR_H
