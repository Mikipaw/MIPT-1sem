//
// Created by mikhalinho on 07.12.2021.
//

#include "CodeAnalyser.h"

int CodeAnalyser::Require(char c) {
    Skipspaces();

    if (*input_code == c) input_code++;
    else return SYNTAX_ERROR;

    return ALL_OK;
}

/*!
 * @method Getblock()
 * @brief gets block of code from input code and definite its type.
 * @return block type
 */
codeblock CodeAnalyser::Getblock() {
    codeblock result(input_code);
    if (EmptyLine()) {
        result.type = EMPTY_LINE;
        result.size = input_code - result.string;

        return result;
    }

    Skipspaces();
    if (input_code[0] == '}') input_code += 4;

    int blocktype = 0;

    while (true) {
        blocktype = Get_Identifier();
        if (blocktype) break;
        else input_code = result.string;

        blocktype = TryGetAss();
        if (blocktype) break;
        else input_code = result.string;


        blocktype = TryGetFunction();
        if (blocktype) {
            TryGetStatement();
            break;
        }

        blocktype = TryGetExpression();
        if (blocktype) break;
        else input_code = result.string;


        blocktype = TryGetStatement();
        if (blocktype) break;
        else input_code = result.string;

        if (input_code[0] == '{' && input_code[1] == '.') {
            input_code ++;
            blocktype = EMPTY_LINE;
            break;
        }

        if (input_code[0] == '}') {
            input_code++;
            blocktype = STOP;
            break;
        }
        Syntax_err;
    }
    if (blocktype == END) {
        input_code[0] = '\0';
        result.size = input_code - result.string;
        result.type = blocktype;
        return result;
    }

    if (input_code[0] != '.') input_code++;
    if (Require("...", 3)) throw std::logic_error("Syntax error! ... expected in the end of the line!\n");
    else {
        input_code[0] = '\0';
        result.size = input_code - result.string;
        result.type = blocktype;
        return result;
    }
}


int CodeAnalyser::Require(const char *str, size_t str_size) {
    for (int i = 0; i < str_size; ++i) {
        if (*input_code != str[i]) return SYNTAX_ERROR;
        input_code++;
    }

    return ALL_OK;
}


bool CodeAnalyser::EmptyLine() {
    char c = input_code[0];

    while (c != '\n') {
        c = *input_code;
        switch (c) {
            case '\n':
                input_code++;
                return true;

            case '\r':
            case '\t':
            case ' ':
            input_code++;
                continue;

            default:
                return false;
        }
    }

    return true;
}


void CodeAnalyser::Skipspaces() {
    while (*input_code == '\r' || *input_code == '\t' || *input_code == ' ' || *input_code == '\n')
        input_code++;
}


int CodeAnalyser::Lexer() {
    codeblock block(nullptr);

    try {
        while (block.type != END) {
            block = Getblock();
            commands.push(block);
            input_code++;
        }   
    } catch (const std::logic_error& err) {
        puts("Invalid code!\n");
        puts(err.what());
    }

    return ALL_OK;
}


int CodeAnalyser::TryGetExpression() {
    if (input_code[0] == '.' && input_code[1] == '.' && input_code[2] == '.') return ZERO;
    while (true) {
        Skipspaces();
        if (!strncmp(input_code, "rad", 3)) {
            input_code += 3;
            continue;
        }

        if (input_code[0] == '.' && input_code[1] == '.') return EXPRESSION;

        if (*input_code == '.') {
            if (input_code[1] != '.') {
                input_code++;
                continue;
            }
            else if (input_code[2] == '.') {
                input_code++;
                return EXPRESSION;
            }
        }

        if (is_digit(*input_code)) {
            input_code++;
            continue;
        }

        if (isalpha(*input_code)) {
            if (is_variable()) {
                input_code++;
                continue;
            }
            else return ZERO;
        }

        switch (*input_code) {
            case ' ':
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
            case '(':
            case ')':
                input_code++;
                continue;

            default:
                return ZERO;
        }
    }
}


bool CodeAnalyser::is_variable() {
    char* name = new char[LIMITED_SIZE_OF_STRING];
    int i = 0;
    while (is_alpha(input_code[i])) {
        name[i] = input_code[i];
        i++;
    }
    name[i] = '\0';

    input_code += i;
    Skipspaces();

    variable tmp_var(name, variables.Get_Length());
    if (variables.HasElement(tmp_var)) {
        //for (int j = 0; j <= i; ++j) input_code++;
        delete[] name;
        return true;
    }
    else {
        delete[] name;
        return false;
    }
}


int CodeAnalyser::TryGetFunction() {
    Skipspaces();
    if (!std::isalpha(*input_code)) return ZERO;

    char* name = new char[LIMITED_SIZE_OF_STRING];
    int size = 0;
    sscanf(input_code, "%s%n", name, &size);

    function tmp_var(name, variables.Get_Length());
    if (functions.HasElement(tmp_var)) {
        for (int j = 0; j <= size + 1; ++j) input_code++;
        Require('(');
        int num_args = functions.search(tmp_var).number_of_args;

        for (int i = 0; i < num_args; ++i) {
            if (is_variable()) input_code++;
            else if (is_digit(*input_code))
                while (is_digit(*input_code)) input_code++;
            else return ZERO;

            if (num_args - i > 1) Require(',');
        }
        Require(')');

        delete[] name;
        return FUNCTION;
    }
    else {
        delete[] name;
        return ZERO;
    }
}


int CodeAnalyser::TryGetStatement() {
    Skipspaces();

    if (*input_code != '{') return ZERO;
    else (*input_code)++;

    char* endofbody = find_close_bracket();

    if (endofbody == nullptr) Syntax_err;

    input_code = endofbody;
    return STATEMENT;
}


int CodeAnalyser::CheckVariable() {
    Skipspaces();

    input_code += 8;            //size of "headache"
    Skipspaces();

    char* name = new char[LIMITED_SIZE_OF_STRING];
    int i = 0;
    while (is_alpha(input_code[i])) {
        name[i] = input_code[i];
        i++;
    }
    name[i] = '\0';

    input_code += i;
    Skipspaces();

    if (*input_code == '.') {
        variables.Add(variable(name, variables.Get_Length()));
        return INITIALISING;
    }
    else if (*input_code == '=') {
        input_code++;
        char* varname = new char[LIMITED_SIZE_OF_STRING];

        if (TryGetExpression()) {
            variables.Add(variable(name, variables.Get_Length()));
            delete[] varname;
            return INITIALISING;
        }
        else if (sscanf(input_code, "%s", varname)) {
            if (variables.HasElement(variable(varname))) {
                input_code += strlen(varname);
                delete[] varname;
                return INITIALISING;
            }
            else Syntax_err;
        }
        else Syntax_err;
    }
    else Syntax_err;
}

int CodeAnalyser::TryGetAss() {
    Skipspaces();

    char* name = new char[LIMITED_SIZE_OF_STRING];
    int i = 0;
    while (is_alpha(input_code[i])) {
        name[i] = input_code[i];
        i++;
    }
    name[i] = '\0';

    input_code += i;
    Skipspaces();

    if (*input_code != '=') return ZERO;
    else {
        if (!variables.HasElement(variable(name))) return UNDECLARED_VARIABLE;

        input_code++;
        char* varname = new char[LIMITED_SIZE_OF_STRING];

        if (TryGetExpression()) {
            delete[] varname;
            return ASSIGNMENT;
        }
        else {
            int lenstr = 0;
            while (is_alpha(input_code[lenstr])) {
                varname[lenstr] = input_code[lenstr];
                lenstr++;
            }
            varname[lenstr] = '\0';
            if (variables.HasElement(variable(varname))) {
                input_code += lenstr;

                delete[] varname;
                return ASSIGNMENT;
            }
            else Syntax_err;
        }
    }

}


int CodeAnalyser::CheckDefine() {
    Skipspaces();

    input_code += 4;            //size of "#def"
    Skipspaces();

    input_code = strchar(input_code, '{');
    if (input_code == nullptr) Syntax_err;
    input_code++;

    char* end_of_def = find_close_bracket();

    if (end_of_def == nullptr) Syntax_err;

    input_code = ++end_of_def;
    return DEFINE;
}


int CodeAnalyser::CheckIf() {
    Skipspaces();

    input_code += 5;            //sizeof "maybe"
    Skipspaces();

    if (*input_code != '(') Syntax_err;
    input_code++;

    char* endofcond = find_close_bracket2();

    if (endofcond == nullptr) Syntax_err;

    input_code = endofcond;
    input_code++;

    Skipspaces();
    if (*input_code != '{') Syntax_err;
    input_code++;

    char* endofbody = find_close_bracket();

    if (endofbody == nullptr) Syntax_err;

    endofbody += 5;

    if (!strncmp(endofbody, "else", 4)) {
        for (int i = 0; i < 4; ++i) endofbody[i] = ' ';
        return IFELSE;
    }
    else return IF;
}

int CodeAnalyser::CheckWhile() {
    Skipspaces();
    input_code += 6;        //sizeof "trying"
    Skipspaces();

    if (*input_code != '(') Syntax_err;
    input_code++;

    char* endofcond = find_close_bracket2();

    if (endofcond == nullptr) Syntax_err;

    input_code = endofcond;
    input_code++;

    Skipspaces();
    if (*input_code != '{') Syntax_err;
    input_code++;

    char* endofbody = find_close_bracket();

    if (endofbody == nullptr) Syntax_err;

    //input_code = endofbody;
    return WHILE;
}

int CodeAnalyser::Get_Identifier() {
    int result = 0;
    for (int i = 0; i < NUMBER_OF_KEYWORDS; ++i) {
        if (strn_equal(keywords[i], input_code)) {
            result = i + 30;
            break;
        }
    }

    switch (result) {
        case MAINE:
            TryGetMain();
            break;

        case INITIALISING:
            CheckVariable();
            break;

        case WHILE:
            CheckWhile();
            break;

        case IF:
            CheckIf();
            break;

        case DEFINE:
            CheckDefine();
            break;

        case PRINT:
            CheckPrint();
            break;

        case SCAN:
            CheckScan();
            break;

        case RAD:
            CheckRad();
            break;


        case END:           return END;
        default:            return ZERO;
    }
    return result;
}


int CodeAnalyser::TryGetMain() {
    Skipspaces();

    input_code += 7;
    Skipspaces();

    if (*input_code != '{') Syntax_err;
    //input_code++;

    char* endofbody = find_close_bracket();
    if (endofbody == nullptr) Syntax_err;

    //input_code = endofbody;
    return MAINE;
}


void CodeAnalyser::print_commands() {
    size_t size = commands.Get_Size();
    for (int i = 0; i < size; ++i) printf("%s\n", commands.at(i).string);
}


char* CodeAnalyser::find_close_bracket() {
    int shift = 1;
    char* ptr = input_code;
    while (shift != 0) {
        ptr++;
        if (ptr[0] == '\0') return nullptr;
        if (ptr[0] == '{') shift++;
        if (ptr[0] == '}') shift--;
    }
    return ptr;
}

char* CodeAnalyser::find_close_bracket2() {
    int shift = 1;
    char* ptr = input_code;
    while (shift != 0) {
        ptr++;
        if (ptr[0] == '\0') return nullptr;
        if (ptr[0] == '(') shift++;
        if (ptr[0] == ')') shift--;
    }

    return ptr;
}

int CodeAnalyser::CheckPrint() {
    input_code += 6;        //size of "print"
    Skipspaces();
    Require('(');

    if (!is_variable() && !is_digit(input_code[0])) Syntax_err;
    while (is_alpha(*input_code) || is_digit(*input_code)) input_code++;
    Skipspaces();

    Require(')');

    return PRINT;
}


int CodeAnalyser::CheckScan() {
    input_code += 5;            //sizeof "steal"
    Skipspaces();
    Require('(');

    if (!is_variable()) Syntax_err;
    Skipspaces();

    Require(')');

    return SCAN;
}

int CodeAnalyser::CheckRad() {
    input_code += 3;
    Skipspaces();

    Require('(');
    input_code++;
    TryGetExpression();
    Require(')');

    return RAD;
}