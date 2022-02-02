//
// Created by mikhalinho on 17.12.2021.
//

#ifndef PROGRAMMINGLANGUAGE_BACKEND_H
#define PROGRAMMINGLANGUAGE_BACKEND_H

#include <cstdio>

#include "compiler.h"

const int MEMORY_FOR_VARS = 1000;


class Translator {
public:
    Translator(const binary_tree& new_tree, const Set<variable>& vars, const Set<function> fcns)
            :   variables(vars),
                functions(fcns),
                tree(new_tree)
    { read_tree(); }


    int Translate();

    ~Translator() {
        //fprintf(output, "HLT");
        fclose(output);
        free(input_text);
    }

    int read_tree();


private:
    int write_node(const Node* node);

private:
    FILE* input;
    FILE* output = fopen("ASMCode.txt", "wb");

    char*   input_text = nullptr;
    int     var_counter = 0;
    int     mark        = 2;

    const   binary_tree     tree;
    const   Set<variable>   variables;
    const   Set<function>   functions;
};





#endif //PROGRAMMINGLANGUAGE_BACKEND_H
