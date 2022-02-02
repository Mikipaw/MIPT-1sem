//
// Created by pawlo on 02.10.2020.
//


#include "Tests.h"

void AllTests(){
    First_test();
    Second_test();
    Third_test();
    Fourth_test();
    //Fifth_test();
    fprintf(stderr, "All tests are OK!\n");
}

//!Checks Stack's methods
void First_test(){
    Stack<int> stk = Stack<int>(5);
    stk.push(2);
    stk.push(4);
    stk.push(88);

    stk.at(1) == 4    asserted;
    stk.at(2) == 88   asserted;
    stk.Get_Capacity() == 5 asserted;
    stk.Get_Size() == 3     asserted;

    int check = 0;

    stk.pop(&check)         asserted;
    check == 88             asserted;
    stk.Get_Size() == 2     asserted;
    stk.Get_Capacity() == 5 asserted;

    stk.push(1);
    stk.push(0);
    stk.push(988);

    stk.Get_Capacity() == 5 asserted;

    stk.push(123);

    stk.Get_Capacity() == 11 asserted;

    Stack_info(stk);

    fprintf(stderr, "First test is OK!\n");
}

//!Checks str_cmp with typeid
void Second_test(){
    const char* str = "String";

    if (str_cmp (typeid(str).name(), "PKc")) fprintf(stderr, "Second test is OK!\n");
    else fprintf(stderr, "Second test was failed!\n%s != PKc\n", typeid(str).name());
}

//!Checks charsum of types
void Third_test() {
    int i = 0;
    double d = 0;
    const char* ccp = "string";
    char* cp = nullptr;
    float f = 3;
    char c = 0;

    int sum1 = charsum(typeid(i).name());
    int sum2 = charsum(typeid(d).name());
    int sum3 = charsum(typeid(ccp).name());
    int sum4 = charsum(typeid(cp).name());
    int sum5 = charsum(typeid(f).name());
    int sum6 = charsum(typeid(c).name());

    sum1 == 'i'             asserted;
    sum2 == 'd'             asserted;
    sum3 == 'P' + 'c' + 'K' asserted;
    sum4 == 'P' + 'c'       asserted;
    sum5 == 'f'             asserted;
    sum6 == 'c'             asserted;

    fprintf(stderr, "Third test is OK!\n");
}

void Fourth_test(){
    Stack<double> stak(3);

    stak.push(2.32);
    stak.push(2);

    stak.Get_Size()     == 2 asserted;
    stak.Get_Capacity() == 3 asserted;

    double rvar = 0;

    stak.pop(&rvar) == 1 asserted;
    stak.pop();
    (rvar - 2) < 10e-6 && (rvar - 2) > -10e-6 asserted;

    stak.Get_Size() == 0 asserted;
    Stack_info(stak);
    //stak.Destruct();
    fprintf(stderr, "Fourth test is OK!\n");
}
