//
// Created by mikipaw on 16.10.2020.
//
#ifndef PROC_ENUM_H
#define PROC_ENUM_H

/*!@enum Commands
 * Commands with numbers from 0 to 21
 */
enum Commands{
#define DEF_CMD(name, num, code, hash) CMD_##name = num,
#include "commands.h"
    NUMBER_OF_COMMANDS,
#undef DEF_CMD
};


#endif //PROC_ENUM_H
