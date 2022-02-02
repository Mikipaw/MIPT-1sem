//
// Created by mikipaw on 18.10.2020.
//

#ifndef PROCESSOR_CPU_H
#define PROCESSOR_CPU_H

#include "Stack.h"
#include "enum.h"
#include "cstring"
#include "List_of_mistakes.h"
#include "CPU_Paths.h"
#include "myStr.h"

#include <GL/gl.h>
#include <GL/glut.h>

class CPU;

/*!
 * @enum Registers
 * @brief Registers in CPU.
 */
enum Registers{
    RAX,        //0
    RBX,        //1
    RCX,        //2
    RDX,        //3
};

#define CREATE_CPU(name, number_of_commands, id) CPU name(number_of_commands, id, #name);


void Display(const CPU& cpu);

/*!
 * @function void CPU_info(const CPU& cpu);
 * @param cpu - const CPU&
 * @brief Function prints some information in CPU.
 * @return nothing.
 */
void CPU_info(const CPU& cpu);

/*! @class CPU
 *  @brief This CPU executes commands from file with codes of coammnds.
 *
 *  @param cpu_stack - stack with double numbers.
 *  @param number_of_commands - number of commands in input file with commands.
 *  @param id - id.
 *  @param version - version.
 *  @param name - name of the CPU.
 *  @param ret - pointer to return back from function.
 *
 *  Some details about the CPU class.
 */
class CPU{
private:
    Stack<double> cpu_stack = Stack<double>(1);
    size_t number_of_commands = 0;
    const char* name = "Unnamed CPU";

    double* reg     = nullptr;
    double* array   = nullptr;
    int* mark       = nullptr;
    double* RAM     = nullptr;

    int ret = 0;
    int id = 0;
    const double version = 3.2;

    int* v_memory;

public:
    explicit
    CPU(size_t num_of_coms, int my_id, const char* new_name);

    double Get_command (int index) const { return array[index]; };


    /*!
    *  @method int Work().
    *  @brief  Executes commands from given file.
    *
    *  @return an integer - error code.
    */
    int Work();

    CPU& operator=(const CPU& cpu) = delete;
    CPU(const CPU&)                = delete;


    void Change_ret(int pointer){ ret = pointer; }

    [[nodiscard]] const char* Get_name()    const { return name; };
    [[nodiscard]] double      Get_version() const { return version; };
    [[nodiscard]] int         Get_id()      const { return id; };
    [[nodiscard]] int         Get_NOC()     const { return number_of_commands; };
    [[nodiscard]] int         Get_ret()     const { return ret; };


    [[nodiscard]] Stack<double> Get_stack() const { return cpu_stack; };

    [[nodiscard]] double    Get_reg (int number) const { return reg[number]; };
    [[nodiscard]] int       V_mem(int index)     const { return (int)RAM[index]; };
    [[nodiscard]] double    ram(int index)       const { return RAM[index]; };

    ~CPU(){
        free(reg);
        //nullptr
        free(array);
        free(mark);
        free(RAM);
    }

};

#endif //PROCESSOR_CPU_H
