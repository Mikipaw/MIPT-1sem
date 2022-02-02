/*!
 *  @mainpage
 *  @brief     Programming language
 *  @author    Michael Pavlov
 *  @author    Mikhail Pavlov
 *  @version   C++20
 *  @date      12.2021
 *  @pre       First initialize the system.
 *  @bug       No
 *  @warning   ...
 *  @copyright GNU Public License.
 */
#include <cstdio>
#include "src/Calculator.h"
#include "src/CodeAnalyser.h"
#include "src/compiler.h"
#include "src/Backend.h"


int main() {
    CodeAnalyser ca("fact.txt");
    ca.Lexer();
    ca.print_commands();
    compiler comp(ca.Get_Stack(), ca.Get_variables(), ca.Get_function());
    comp.Dump();
    comp.Print_tree_in_file();

    Translator ttor(comp.GetTree(), comp.Getvars(), comp.Getfunctions());

    ttor.Translate();

    return 0;
}

