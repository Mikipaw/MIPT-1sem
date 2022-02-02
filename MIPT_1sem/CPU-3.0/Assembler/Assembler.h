//
// Created by mikipaw on 17.10.2020.
//

#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H

#include "myStr.h"
#include "enum.h"
#include "List_of_mistakes.h"
#include "CPU_Paths.h"

/*!
*  \function bool Is_push(const char* str);
*  \brief Function checks if string is "PUSH "
*  \param str a const char*
*  \return true or false
*/
bool Is_push(const char* str);

bool Is_push_reg(const char* str);

/*!
*  \function int Assembler(int* number_of_cmds = nullptr);
*  \brief Classic assembler.
*  \param number_of_cmds an int* - number of commands
*  \return an integer - error code.
*/
int Assembler(int* number_of_cmds = nullptr);

/*!
*  \function void ASM_Listing();
*  \brief Function creates listing file.
*  \param number_of_cmds an int* - number of commands.
*  \return error code.
*/
int ASM_Listing();

/*!
 * \function bool Is_jmp(const char* str);
 * \brief function checks if string is jump.
 * \param str - const char* - command.
 * \return true if true, false if not.
 */
bool Is_jmp(const char* str);

bool Is_RAM(simple_string sstr, int lencom);

/*!
 * @function void Fill_marks(simple_string* commands, size_t* number_of_commands, int** pointers);
 * @brief Function fills the marks in array with commands.
 * @param commands - simple_string* - array with commands.
 * @param number_of_commands - size_t* - pointer to number of commands in array.
 * @param pointers - array with pointers (marks).
 * @return nothing.
 */
void Fill_marks(simple_string* commands, const size_t* number_of_commands, int* pointers);

/*!
 * @function int Hash(const char* string)
 * @brief Functions finds hash of command.
 * @param string
 * @return sum of chars in command name.
 */
int Hash(const char* string);


#define DIE fprintf(stderr, "Assertion failed!\nERROR on line %d\n", __LINE__);

#define asserted || DIE

inline bool Is_reg(const char* str){
    return str[0] == 'R';
    //return str[0] == 'R' && str[2] == 'X' && str[1] >= 'A' && str[1] <= 'D';
}

inline bool Is_push(const char* str){
    return !strncmp(str, "PUSH", 4);
}

inline bool Is_pop(const char* str){
    return !strncmp(str, "POP", 3);
}

bool Is_RAM(simple_string sstr);

#endif