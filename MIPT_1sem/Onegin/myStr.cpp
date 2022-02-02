#include <cstring>
#include <cassert>
#include "myStr.h"

size_t Size_of_file(FILE* name_of_file) {
    fseek(name_of_file, 0, SEEK_END);
    size_t size_of_file = ftell(name_of_file);
    fseek(name_of_file, 0, SEEK_SET);

    return size_of_file;
}


void Print_In_File(simple_string* pointers, FILE* result_file, int number_of_lines, int number_of_empty_lines){
    for (int i = number_of_empty_lines; i < number_of_lines; ++i) {
        if (str_cmp(pointers[i].string, "\0") || str_cmp(pointers[i].string, "\r")
        || str_cmp(pointers[i].string, "\n") || str_cmp(pointers[i].string, " \n")) continue;
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

