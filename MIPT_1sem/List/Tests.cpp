//
// Created by mikipaw on 06.11.2021.
// Copyright (c) 2021 MIPT. All rights reserved.
//

#include "Tests.h"

int Tests() {
    if (Test_push_delete())     return TEST_PUSH_DELETE_ERROR;
    if (Test_get())             return TEST_GET_ERROR;
    if (Test_linear())          return TEST_LINEAR_ERROR;

    return TEST_ALL_OK;
}

bool Test_push_delete() {
    List lst(5);
    lst.Insert(0, 4);
    lst.Insert(1, 3);
    lst.Delete_elem(1);

    return (lst.Get_phys(2) != 3);
}

bool Test_get() {
    List lst(5);
    lst.Insert(0, 4);
    lst.Insert(1, 3);

    if (lst.Get_phys(2) != 3) return true;
    lst.Delete_elem(1);

    return false;
}

bool Test_linear() {
    List lst(6);
    lst.Insert(0, 4);
    lst.Insert(1, 3);
    lst.Insert(1, 8);
    lst.Insert(0, 11);

    lst.Linear();

    for (int i = 1; i <= lst.Get_size(); ++i) {
        if (lst.Get_logical_pos(i) != i) return true;
    }

    return false;
}
