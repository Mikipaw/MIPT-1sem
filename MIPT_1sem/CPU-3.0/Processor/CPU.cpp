//
// Created by mikipaw on 18.10.2020.
//

#include "CPU.h"

void CPU_info(const CPU& cpu){
    printf("CPU = [%p], \"%s\"\n", &cpu, cpu.Get_name());
    printf("{\n");
    printf("\tversion = %.1lf\n",   cpu.Get_version());
    printf("\tid = %d\n",           cpu.Get_id());

    printf("\tRegisters:\n");
    printf("\t{\n");
    printf("\t\tRAX = %lf\n", cpu.Get_reg(RAX));
    printf("\t\tRBX = %lf\n", cpu.Get_reg(RBX));
    printf("\t\tRCX = %lf\n", cpu.Get_reg(RCX));
    printf("\t\tRDX = %lf\n", cpu.Get_reg(RDX));
    printf("\t}\n");

    printf("\tArray:\n");
    printf("\t{\n");
    for(int i = 0; i < cpu.Get_NOC(); ++i) {
        printf("\t%d : %X\n", i, (int) cpu.Get_command(i));
    }
    printf("\t}\n");

    printf("\t RAM:\n");
    printf("\t{\n");
    for(int i = 0; i < 2000; ++i) {
        if(i % 40 == 0) printf("\n");
        printf(" %.1lf", cpu.ram(i));
    }
    printf("\n\t}\n");
    printf("}\n");
}


int CPU::Work(){
    double first    = 0;
    double second   = 0;
    int    integ    = 0;
    for(int i = 0; i < number_of_commands; ++i) {
        integ = (int) array[i];
        switch (integ) {
#define DEF_CMD(name, num, code, hash){                                 \
                    case num:                                           \
                    code;                                               \
                    break;                                              \
                }
#include "commands.h"

#undef DEF_CMD
            default:
                return ERROR_UNKNOWN_COMMAND;
        }
        printf("%d\n", i);
    }

    return ALL_OK;
}

CPU::CPU(size_t num_of_coms, int my_id, const char* new_name):
        number_of_commands      (num_of_coms),
        id                      (my_id),
        reg                     (new double[5]),
        cpu_stack               (1, "CPU Stack"),
        mark                    (new int[5]),
        name                    (new_name),
        RAM                     (new double[2000])
{
    for(int i = 0; i < 5; ++i) {
        reg[i] = 0;
        mark[i] = 0;
    }

    v_memory = (int*) RAM;         //40x30

    FILE* input = fopen(_output_file, "rb");
    assert(input != nullptr);

    size_t size_of_file = Size_of_file(input);
    size_t non = 0;

    char* text = simple_text_from_file(input, size_of_file + 1, &non);
    fclose(input);

    array = (double*) calloc(non + 1, sizeof(double));

    double doub = 0;
    int pos = 0;
    int j = 0;
    size_t lenstr = strlen(text);

    double magnitude = 10;
    while(pos < lenstr) {
        magnitude = 10;
        sscanf(text + pos, "%lf", &doub);
        array[j++] = doub;
        pos+=2;
        while(doub >= magnitude){
            pos++;
            magnitude*=10;
        }
        doub*=100;
        if(      (int) doub % 10  != 0) pos+=3;
        else if( (int) doub % 100 != 0) pos+=2;
    }

    number_of_commands = non;
};
