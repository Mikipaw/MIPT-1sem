//
// Created by mikipaw on 06.11.2021.
// Copyright (c) 2021 MIPT. All rights reserved.
//

#ifndef LIST_TESTS_H
#define LIST_TESTS_H

#include "List.h"

enum {
    TEST_ALL_OK      = 0,
    TEST_PUSH_DELETE_ERROR = 1,
    TEST_GET_ERROR = 2,
    TEST_LINEAR_ERROR = 3,
};

int Tests();

bool Test_push_delete();
bool Test_get();
bool Test_linear();

#endif //LIST_TESTS_H
