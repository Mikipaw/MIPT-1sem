//
// Created by mikipaw on 20.09.2020.
//
#pragma once

#ifndef ONEGIN_TESTS_H
#define ONEGIN_TESTS_H

#include <cassert>
#include "myStr.h"

void AllTests();
void strcmp_Test();


void AllTests(){
    strcmp_Test();
    fprintf(stderr, "All tests are OK!\n");
}

void strcmp_Test() {
    simple_string uno;
    uno << "Milk";
    simple_string dos;
    dos << "Milk";
    simple_string trs;
    trs << "NotMilk";
    const char* qdr = "";
    const char* cnc = "";
    simple_string sis;
    sis << "Filk";
    simple_string sit;
    sit << "Z";
    simple_string och;
    och << "z";
    simple_string nve;
    nve << "Milk ";
    assert( str_cmp(uno.string, dos.string));
    assert(!str_cmp(uno.string, trs.string));
    assert( str_cmp(qdr, cnc));
    assert(!str_cmp(uno.string, sis.string));
    assert(!str_cmp(uno.string, qdr));
    assert(!str_cmp(sit.string, och.string));
    assert(!str_cmp(uno.string, nve.string));
    fprintf(stderr, "Test str_cmp function is OK!\n");
    simple_string* pointers = (simple_string*) calloc(8, sizeof(simple_string));
    pointers[0] = uno;
    pointers[1] = dos;
    pointers[2] = trs;
    pointers[4] = sis;
    pointers[5] = nve;
    pointers[6] = sit;
    pointers[7] = och;
    assert(!str_cmp(pointers[0].string, "Flik"));
    assert(str_cmp(pointers[0].string, pointers[1].string) && pointers[0].size == pointers[1].size);
    assert(pointers[6].size == pointers[7].size);
    free(uno.string);
    free(dos.string);
    free(trs.string);
    free(sis.string);
    free(sit.string);
    free(och.string);
    free(nve.string);
    free(pointers);
    fprintf(stderr, "Test str_cmp_4_sort function is OK!\n");
}



#endif //ONEGIN_TESTS_H
