//
// Created by mikipaw on 29.09.2020.
//
#ifndef STACK_TESTS_H
#define STACK_TESTS_H
#include "Stack.h"

#define DIE fprintf(stderr, "Assertion failed!\nERROR on line %d\n", __LINE__);

#define asserted || DIE

/*!
 * @test First_test().
 * @brief Test checks class methods
 */
void First_test();

/*!
 * @test Second_test().
 * @brief Test checks typeid(type).name().
 */
void Second_test();

/*!
 * @test Third_test().
 * @brief Test checks charsum() function.
 */
void Third_test();

/*!
 * @test Fourth_test().
 * @brief Test checks stack with doubles.
 */
void Fourth_test();



void AllTests();

#endif //STACK_TESTS_H
