//
// Created by mikhalinho on 17.11.2021.
//

#include <cassert>
#include "mystr.h"

char* text_from_file(FILE* file_name, size_t size_of_file) {
    char* result_string = (char*) calloc(size_of_file + 5, sizeof(char));
    fread(result_string, sizeof(char), size_of_file + 5, file_name);
    result_string[size_of_file] = '\0';

    return result_string;
}

size_t Size_of_file(FILE* name_of_file) {
    fseek(name_of_file, 0, SEEK_END);
    size_t size_of_file = ftell(name_of_file);
    fseek(name_of_file, 0, SEEK_SET);

    return size_of_file;
}

bool is_digit(char c) {
    return c >= '0' && c <= '9' || c == '.';
}

bool isvar(char c) {
    return c >= 'a' && c <= 'z';
}

bool is_alpha(char c) {
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}



/*!
 * @function strchar(char* buffer, char sym)
 * @brief Function finds the first symbol 'sym' in string 'buffer' and returns pointer to it (or nullptr if wasn't found)
 * @param buffer - char* (source string)
 * @param sym - char (symbol user wants to find)
 * @return char* - pointer to the first symbol 'sym' in 'buffer'
 */
char* strchar(char* buffer, char sym) {
    char* c = buffer;
    while (*c != sym) {
        c++;
        if (c == nullptr) return c;
        if (*c == '\0') return c;
    }

    return c;
}

char* to_str(int a) {
    char* result = new char[10];
    sprintf(result, "%d", a);
    return result;
}

void  SkipSpaces (char** code) {
    assert (code);
    //assert (*code);

    //while (**code == ' ' || **code == '\t' || **code == '\r' || **code == '\n') (*code)++;
}

char* strlinechar(char* buffer, char sym) {
    char* c = buffer;
    while (*c != sym) {
        c++;
        if (c == nullptr) return c;
        if (*c == '\0') return nullptr;
    }

    return c;
}

bool strn_equal(const char* str1, const char* str2) {
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    int counter = 0;
    while (true) {
        if (str1[counter] != str2[counter]) return false;

        counter++;
        if (!is_alpha(str1[counter]) || !is_alpha(str2[counter])) return true;
    }

}