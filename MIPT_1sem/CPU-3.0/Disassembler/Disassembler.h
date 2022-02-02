//
// Created by pawlo on 13.10.2021.
//

#ifndef DISASSEMBLER_DISASSEMBLER_H
#define DISASSEMBLER_DISASSEMBLER_H

#include "myStr.h"
#include "enum.h"
#include "List_of_mistakes.h"
#include "CPU_Paths.h"

int Disassembler();

inline bool Is_arg(int command) {
    return command >= 20;
}

#endif //DISASSEMBLER_DISASSEMBLER_H
