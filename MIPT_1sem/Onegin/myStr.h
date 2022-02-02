//
// Created by mikipaw on 20.09.2020.
//
#ifndef ONEGIN_MYSTR_H
#define ONEGIN_MYSTR_H

#define TRUE 1
#define FALSE 0

#include <cstring>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cassert>

/*!
 *  \struct simple_string
 *  \param string a char*
 *  \param size a size_t - size of string
 */
struct simple_string{
    simple_string() = default;
    char* string = nullptr;
    size_t size = 0;
};


/*!
*  \function int str_cmp(const char* str1, const char* str2)
*  \brief Function checks if 2 strings are equal
*  \param str1 a const char*
*  \param str2 a const char*
*  \return an integer - true(1) or false(0)
*/
int str_cmp(const char* str1, const char* str2);


/*!
*  \function int str_cmp_4_sort(const char* str1, const char* str2)
*  \brief Function compares 2 strings
*  \param str1 a const char*
*  \param str2 a const char*
*  \return an integer: >0 if str1 > str2, =0 if str1 == str2, <0 if str1 < str2
*/
int str_cmp_4_sort(const char* str1, const char* str2);

/*!
*  \function int str_cmp_4_sort_from_end(const char* str1, const char* str2)
*  \brief Function compares 2 strings from last symbol
*  \param str1 a const simple_string
*  \param str2 a const simple_string
*  \return an integer: >0 if str1 > str2, =0 if str1 == str2, <0 if str1 < str2
*/
int str_cmp_4_sort_from_end(const simple_string& str1, const simple_string& str2);


/*!
*  \function void quick_sort_strings(char** array, int left, int right, const char* order = "FROM BEGIN");
*  \brief Function sorts the array of strings
*  \param array a char** - array of strings
*  \param left an integer - left border of array
*  \param right an integer - right border of array
*  \param order a const char*
*  \return nothing
*/
void quick_sort_strings(simple_string* array, int left, int right, const char* order = "FROM BEGIN");

/*!
*  \function void Print_In_File(simple_string* array, FILE* result_file);
*  \brief Function prints the array of strings in file
*  \param array a char** - array of strings
*  \param result_file a FILE*
*  \return nothing
*/
void Print_In_File(simple_string* pointers, FILE* result_file, int number_of_lines, int number_of_empty_lines = 0);


/*!
*  \function size_t Size_of_file(FILE* name_of_file);
*  \brief Function finds size of file
*  \param name_of_file - a FILE*
*  \return size_t - number of chars
*/
size_t Size_of_file(FILE* name_of_file);


/*!
*  \function int Arrange_str_ptrs(simple_string* pointers, size_t number_of_lines, char* text);
*  \brief Function fills the array and count number of empty lines.
*  \param pointers a simple_string*
*  \param number_of_lines a size_t
*  \param text a char*
*  \return int - number of empty strings
*/
int Arrange_str_ptrs(simple_string* pointers, size_t number_of_lines, char* text);

simple_string& operator<<(simple_string& sstr, const char* str);

/*!
*  \function char* text_from_file(FILE* file_name)
*  \brief Returns text from file_name
*  \param file_name a FILE*
*  \param size_of_file a size_t
*  \param number_of_lines a size_t*
*  \return a char* - text from file
*/
char* text_from_file(FILE* file_name, size_t size_of_file, size_t* number_of_lines);





/*
size_t Size_of_file(FILE* name_of_file) {
    fseek(name_of_file, 0, SEEK_END);
    size_t size_of_file = ftell(name_of_file);
    fseek(name_of_file, 0, SEEK_SET);

    return size_of_file;
}


void Print_In_File(simple_string* pointers, FILE* result_file, int number_of_lines, int number_of_empty_lines){
    for (int i = number_of_empty_lines; i < number_of_lines; ++i) {
        if (str_cmp(pointers[i].string, "\0") || str_cmp(pointers[i].string, "\r") || str_cmp(pointers[i].string, "\n")) continue;
        fwrite(pointers[i].string, pointers[i].size, sizeof(char), result_file);
    }
}

int simple_string_comparator(const simple_string& string1, const simple_string& string2){
    return str_cmp_4_sort(string1.string, string2.string);
}

void quick_sort_strings(simple_string* array, int left, int right, const char* order){
    simple_string tmp = array[left];
    int l_hold = left, r_hold = right, mdl = 0;
    while (left < right){
        if (str_cmp(order, "FROM END")){
            while((str_cmp_4_sort_from_end(array[right], tmp) >= 0) && (left < right)) right--;
            if(left != right) array[left++] = array[right];
            while((str_cmp_4_sort_from_end(array[left], tmp) <= 0) && (left < right)) left++;
            if(left != right) array[right--] = array[left];
        }
        else{
            while((str_cmp_4_sort(array[right].string, tmp.string) >= 0) && (left < right)) right--;
            if(left != right) array[left++] = array[right];
            while((str_cmp_4_sort(array[left].string, tmp.string) <= 0) && (left < right)) left++;
            if(left != right) array[right--] = array[left];
        }

    }
    array[left] = tmp;
    mdl = left;
    left = l_hold;
    right = r_hold;
    if (left < mdl)  quick_sort_strings(array, left, mdl - 1, order);
    if (right > mdl) quick_sort_strings(array, mdl + 1, right, order);
}

int str_cmp_4_sort_from_end(const simple_string& str1, const simple_string& str2){
    int i = str1.size, j = str2.size;
    if (i == 0 || j == 0)
        return i - j;

    i--;
    j--;

    while(i >= 0 && j >= 0){
        while(!(isalpha(str1.string[i]))) i--;
        while(!(isalpha(str2.string[j]))) j--;

        if (i < 0 && j < 0)
            return 0;
        else if (i < 0 || j < 0)
            return i - j;

        while(str1.string[i] == str2.string[j] && i > 0 && j > 0){
            i--;
            j--;
        }
        return str1.string[i] - str2.string[j];
    }

    return 0;
}


int str_cmp_4_sort(const char* str1, const char* str2){
    int i = 0, j = 0;
    while(TRUE){
        while(!(isalpha(str1[i]) || str1[i] == '\0')) i++;
        while(!(isalpha(str2[j]) || str2[j] == '\0')) j++;

        if (str1[i] == '\0' &&
            str2[j] == '\0')
            return 0;

        if (str1[i] == str2[j]){
            i++;
            j++;
        }

        else
            return str1[i] - str2[j];
    }
}


int str_cmp(const char* str1, const char* str2){
    int i = 0;
    while(TRUE){
        if(str1[i] == '\0' && str2[i] == '\0') return TRUE;
        if(str1[i] == str2[i]){
            ++i;
            continue;
        }
        return FALSE;
    }
}

simple_string &operator<<(simple_string &sstr, const char *str) {
    char c = 1;
    int size = 0;
    while(c != '\0'){
        c = str[size++];
    }
    sstr.string = (char*) calloc(size, sizeof(char));
    sstr.string = (char*) str;
    sstr.size = size;
    return sstr;
}

int Arrange_str_ptrs(simple_string* pointers, const size_t number_of_lines, char* text) {
    assert(pointers != nullptr);
    assert(text != nullptr);
    int number_of_empty_lines = 0;
    //char *ptr = text;
    for (int i = 1; i < number_of_lines; ++i) {
        text = strchr(text, '\0');
        text++;
        pointers[i].string = text;
        pointers[i - 1].size = (int) (pointers[i].string - pointers[i - 1].string);
        if (pointers[i - 1].string[0] == '\n')
            number_of_empty_lines++;
    }

    return number_of_empty_lines;
}

*/
#endif //ONEGIN_MYSTR_H
