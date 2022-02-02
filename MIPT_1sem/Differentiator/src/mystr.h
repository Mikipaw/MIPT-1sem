//
// Created by mikhalinho on 17.11.2021.
//

#ifndef AKINATOR_MYSTR_H
#define AKINATOR_MYSTR_H

#include <cstdio>
#include <cstdlib>

const int LIMITED_SIZE_OF_STRING = 100;
const int LIMITED_BUFFER_SIZE    = 1000;
const int SHORT_TMP_STRING_SIZE  = 10;

char* text_from_file(FILE* file_name, size_t size_of_file, size_t* number_of_lines);

/*!
*  \function size_t Size_of_file(FILE* name_of_file);
*  \brief Function finds size of file
*  \param name_of_file - a FILE*
*  \return size_t - number of chars
*/
size_t Size_of_file(FILE* name_of_file);

bool is_digit(char c);

bool isvar(char c);

#endif //AKINATOR_MYSTR_H
