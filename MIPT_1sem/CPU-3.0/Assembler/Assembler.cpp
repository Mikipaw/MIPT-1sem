#include "Assembler.h"

bool Is_RAM(simple_string sstr, int lencom) {
    return sstr.string[lencom] == '[';
}

bool Is_jmp(const char* str){
    return str[0] == 'J';
}

bool Is_push_reg(const char* str){
    if(str[0] != 'P')                           return false;
    if(str[5] != 'R' && str[7] != 'X')          return false;
    if(str[6] - 'A' >= 4 || str[6] - 'A' < 0)   return false;

    return true;
}


int Hash(const char* string) {
    char c = 1;
    int result = 0;

    int i = 0;
    if (string[0] == ' ') ++i;

    for (; c != ' ' && c != '\0'; ++i) {
        c = string[i];
        if(c != ' ' && c != '\n') result += (int) c;
    }
    return result;
}

void Fill_marks(simple_string* commands, const size_t* number_of_commands, int* pointers){
    int arguments = 0;
    for(int i = 0; i < *number_of_commands; ++i) {
        if (Is_RAM(commands[i])) {
            arguments += 2;
            continue;
        }
        if (Is_pop(commands[i].string) || Is_jmp(commands[i].string)) arguments++;
        else if( Is_push(commands[i].string)){
            if(!Is_push_reg(commands[i].string)) arguments++;
            arguments++;
        }
        if(commands[i].string[1] == ':'){
            pointers[commands[i].string[0] - '0'] = i + arguments;
            arguments--;
            //(*number_of_commands)--;
        }
    }
}

int Assembler(int* number_of_cmds) {
    size_t number_of_commands = 0;
    simple_string* array_with_commands = Make_array_from_text_file(_input_programm, &number_of_commands);

    FILE* output = fopen(_output_file, "wb");
    if(!output) return ERROR_OPENING_FILE;

    int* pointers = (int*) calloc(6, sizeof(int));
    Fill_marks(array_with_commands, &number_of_commands, pointers);

    int reg_number = 0;
    int chash = 0;
    int lencom = 0;
    for(int i = 0; i < number_of_commands; ++i) {
        chash = Hash(array_with_commands[i].string);
        switch (chash) {
    #define DEF_CMD(name, number, code, hash){                                      \
                case hash:                                                                  \
                    lencom = strlen(#name) + 1;                                             \
                    fprintf(output, "%d ", number);                                         \
                    if(Is_jmp(array_with_commands[i].string)){                              \
                    sscanf(array_with_commands[i].string + lencom + 1, "%d", &reg_number);  \
                    fprintf(output, "%d ", pointers[reg_number]);                           \
                    break;                                                                  \
                }                                                                           \
                break;                                                                      \
        }


#include "commands.h"

            default:
                //printf("%d\n", chash);
                break;
        }
        if (Is_push(array_with_commands[i].string) ||
            Is_pop(array_with_commands[i].string)) {
            if(Is_RAM(array_with_commands[i], lencom)) {
                fprintf(output, "5 ");
                lencom++;
            }

            if(array_with_commands[i].string[lencom] == 'R')
                fprintf(output, "%d ", array_with_commands[i].string[lencom + 1] - 'A' + 1);
            else
                fprintf(output, "0 %s ", array_with_commands[i].string + lencom);
        }
#undef DEF_CMD
    }

    *number_of_cmds = number_of_commands;

    fclose(output);
    free(pointers);
    free(array_with_commands);
    return 2;
}

int ASM_Listing(){
    size_t number_of_commands = 0;

    simple_string*
            array_with_commands = Make_array_from_simple_text_file(_output_file, &number_of_commands);

    FILE* ASM_Listing = fopen("ASM_Listing.txt", "wb");

    const char* regs = "\t\0RAX\0RBX\0RCX\0RDX\0RAM\0";
    simple_string* rip = (simple_string*) calloc(5, sizeof(simple_string));
    rip[0].string = (char*) regs;

    Arrange_str_ptrs(rip, 5, (char*) regs);

    int command     = 0;
    int pos         = 1;
    int arg         = 0;
    double num      = 0;

    for(int i = 0; i < number_of_commands; ++i){
        sscanf(array_with_commands[i].string, "%d", &command);
        arg = command / 20;
        switch (command) {
#define DEF_CMD(name, number, code, hash){                                                              \
                case number:                                                                                        \
                    if(arg == 0) {                                                                                  \
                        fprintf(ASM_Listing, "%X\t%d\t\t\t\t%s\n", pos++, number, #name);                           \
                        break;                                                                                      \
                    }                                                                                               \
                    else if(arg == 1){                                                                              \
                        sscanf(array_with_commands[i++].string, "%*d %d", &command);                                \
                        if(Is_push(#name) || Is_pop(#name))                                                         \
                        fprintf(ASM_Listing, "%X\t%d\t%d\t\t\t%s %s\n", pos, number, command, #name, rip[command]); \
                        else                                                                                        \
                        fprintf(ASM_Listing, "%X\t%d\t%d\t\t\t%s %d\n", pos, number, command, #name, command);      \
                        pos += 2;                                                                                   \
                        break;                                                                                      \
                    }                                                                                               \
                    else if(arg == 2){                                                                              \
                        sscanf(array_with_commands[i+=2].string, "%*d %d %lf", &command, &num);                     \
                        fprintf(ASM_Listing, "%X\t%d\t0\t%.2lf\t%s %lf\n", pos, number, num, #name, num);           \
                        pos += 3;                                                                                   \
                        break;                                                                                      \
                    }                                                                                               \
            }

#include "commands.h"
            default:
                printf("%d\n", command);
                break;
#undef DEF_CMD

        }
    }

    fclose(ASM_Listing);
    free(array_with_commands);
    return ALL_OK;
}

bool Is_RAM(simple_string sstr) {
    if (sstr.string[0] != 'P') return false;

    int i = 4;
    if (sstr.string[i] == ' ') i++;

    return sstr.string[i] == '[';
}

#undef asserted
#undef DIE
