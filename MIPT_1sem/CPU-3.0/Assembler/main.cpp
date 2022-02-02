#include <cstdio>

#include "Assembler.h"

int main() {
    int number_of_cmds = 6;
    Assembler(&number_of_cmds);
    //ASM_Listing();

    FILE* noc = fopen (_number_of_commands, "wb");
    fprintf(noc, "%d", number_of_cmds);
    fclose(noc);

    int a = 0;
    return 0;
}
