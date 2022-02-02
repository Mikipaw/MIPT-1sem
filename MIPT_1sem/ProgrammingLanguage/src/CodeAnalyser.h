//
// Created by mikhalinho on 07.12.2021.
//

#ifndef PROGRAMMINGLANGUAGE_CODEANALYSER_H
#define PROGRAMMINGLANGUAGE_CODEANALYSER_H

#include "mystr/mystr.h"
#include "Error_codes.h"
#include "Enums.h"
#include "Stack.h"
#include "Set.h"

#include "stdexcept"

#define Syntax_err throw std::logic_error(to_str(__LINE__))

class CodeAnalyser {

public:
    explicit CodeAnalyser(const char* input_file) {
        FILE* filecode = fopen(input_file, "rb");

        if (filecode == nullptr) throw std::runtime_error("File wasn't open!\n");

        size_t size_of_file = Size_of_file(filecode);

        input_code = (char*) calloc(size_of_file, sizeof(char) + 1);

        input_code = text_from_file(filecode, size_of_file);

        variables.Add(variable((char*) "ZERO", NAN));
        functions.Add(function((char*) "problem", 0, 0));

        fclose(filecode);
    }


    ~CodeAnalyser() {
        commands.clear();
    }

public:
    int TryGetBody();


    codeblock Getblock();


    bool is_variable();


    void print_commands();


    int Lexer();

    [[nodiscard]] Stack         Get_Stack()     const { return commands; };
    [[nodiscard]] Set<variable> Get_variables() const { return variables; };
    [[nodiscard]] Set<function> Get_function()  const { return functions; };



private:
    void Skipspaces();


    char* find_close_bracket();
    char* find_close_bracket2();
    //int TryGetNumber();


    int Get_Identifier();


    int TryGetFunction();


    int TryGetStatement();


    int TryGetExpression();


    int CheckVariable();


    int TryGetAss();


    int TryGetMain();


    //int TryGetLogical();


    int CheckWhile();


    int CheckIf();


    int CheckDefine();


    int CheckPrint();


    int CheckScan();


    int CheckRad();


    bool EmptyLine();


    int Require(char c);


    int Require(const char* str, size_t str_size);

private:
    char* input_code = nullptr;
    Stack commands = Stack(DEFAULT_STACK_SIZE, "Stack with commands");
    Set<variable> variables;
    Set<function> functions;

    const int NUMBER_OF_KEYWORDS = 9;
    const char* keywords[LIMITED_SIZE_OF_STRING] = {"problem",
                                                    "headache",
                                                    "trying",
                                                    "maybe",
                                                    "#def",
                                                    "mumble",
                                                    "steal",
                                                    "rad",
                                                    "{END}"
                                                        };
};

#endif //PROGRAMMINGLANGUAGE_CODEANALYSER_H
