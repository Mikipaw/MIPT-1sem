/*!
 * @mainpage
 *  \brief     Romeo and Juliet
 *  \details   This program is used to make an encyclopedia using "Romeo and Juliet" tragedy.
 *  \author    Michael Pavlov
 *  \author    Mikhail Pavlov
 *  \version   C++20
 *  \date      09.2020
 *  \pre       First initialize the system.
 *  \bug       No
 *  \warning
 *  \copyright GNU Public License.
 */

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "Tests.h"

const char* FILENAME = "RaJ.txt";

enum ERRORS {
    ALL_OK,
    ERR_OPEN_FILE,
    EMPTY_FILE,
};


int Interface();

int main() {
    AllTests();

    switch (Interface()) {
        case 1:
            printf("Error opening file\n");
        case 2:
            printf("File is empty!");
        default: break;
    }

    return 0;
}

char* text_from_file(FILE* file_name, size_t size_of_file, size_t* number_of_lines){
    char* result_string = (char*) calloc(size_of_file + 5, sizeof(char));
    fread(result_string, sizeof(char), size_of_file + 5, file_name);

    for(int i = 0; i < size_of_file; ++i){
        if(result_string[i] == '\r'){
            result_string[i++]  = '\n';
            result_string[i]    = '\0';
            (*number_of_lines)++;
        }
    }
    return result_string;
}

int Interface() {

    //Program opens the file "Romeo and Juliet"
    FILE* original_text = fopen(FILENAME,    "rb");
    FILE* result_file   = fopen("Result.txt", "wb");

    if (original_text == nullptr || result_file == nullptr) {
        fprintf(stderr, "Error opening file!\n");
        return ERR_OPEN_FILE;
    }

    size_t size_of_file = Size_of_file(original_text);
    assert(size_of_file != 0);

    size_t number_of_lines = 0;
    char* text = text_from_file(original_text, size_of_file, &number_of_lines);
    if (text == nullptr)        return EMPTY_FILE;
    if (number_of_lines == 0)   return EMPTY_FILE;
    printf("Number of lines in input text - %d\n", number_of_lines);

    simple_string *pointers = (simple_string *) calloc(number_of_lines + 1, sizeof(simple_string));
    pointers[0].string = text;

    int number_of_empty_lines = 0;

    number_of_empty_lines = Arrange_str_ptrs(pointers, number_of_lines, text);
    //pointers[number_of_lines-1].size = (int) (pointers[number_of_lines].string - pointers[number_of_lines-1].string);

    //Program prints sorted text in the file
    quick_sort_strings(pointers, 0, number_of_lines - 1);
    fprintf(result_file, "\nSorted from begin:\n");
    Print_In_File(pointers, result_file, number_of_lines, number_of_empty_lines);

    //Program prints sorted from end text in the file
    quick_sort_strings(pointers, 0, number_of_lines - 1, "FROM END");
    fprintf(result_file, "\nSorted from end:\n");
    Print_In_File(pointers, result_file, number_of_lines, number_of_empty_lines);

    //Program prints original text again
    fprintf(result_file, "\nFinal text:\n");
    fwrite(text, size_of_file, sizeof(char), result_file);

    //Closing files and free the memory
    fclose(original_text);
    fclose(result_file);

    free(pointers);
    free(text);

    return ALL_OK;
}



