//
// Created by mikipaw on 22.10.2020.
//

#include "Disassembler.h"

int Disassembler(){
    size_t number_of_commands = 0;
    simple_string*
            array_with_commands = Make_array_from_simple_text_file(_output_file, &number_of_commands);

    FILE* Transed_back = fopen(_translated_back, "wb");

    const char* regs = "\t\0RAX\0RBX\0RCX\0RDX\0";
    simple_string* rip = (simple_string*) calloc(5, sizeof(simple_string));
    rip[0].string = (char*) regs;

    Arrange_str_ptrs(rip, 5, (char*) regs);

    int     mark    = 1;
    int     command = 0;

    int marks[5];
    int j = 1;
    for(int i = 0; i < number_of_commands; ++i){
        sscanf(array_with_commands[i].string, "%d", &command);
        if(command >= CMD_JMP && command <= CMD_JNE){
            sscanf(array_with_commands[++i].string, "%d", &command);
            marks[j++] = command;
        }
    }

    double num = 0;
    j = 1;
    for(int i = 0; i < number_of_commands; ++i){
        if(i == marks[j]){
            fprintf(Transed_back, "%d:\n", j);
            j++;
        }
        sscanf(array_with_commands[i].string, "%d", &command);
#define DEF_CMD(name, number, code, hash){                              \
        if(command == number){                                                  \
        fprintf(Transed_back, "%s ", #name);                                    \
        if(Is_arg(command)) {                                                   \
            sscanf(array_with_commands[++i].string, "%d", &command);            \
            if (number == CMD_PUSH && command == 0){                            \
                sscanf(array_with_commands[++i].string, "%lf", &num);           \
                fprintf(Transed_back, "%lf", num);                              \
                }                                                               \
            else if(number == CMD_PUSH || number == CMD_POP)                    \
                fprintf(Transed_back, "%s ", rip[command]);                     \
            else fprintf(Transed_back, "%d:", mark++);                          \
        }                                                                       \
        fprintf(Transed_back, "\n");                                            \
        continue;                                                               \
        }                                                                       \
        }                                                                       \

#include "commands.h"

#undef DEF_CMD


    }


    fclose(Transed_back);
    free(array_with_commands);
    return ALL_OK;
}

