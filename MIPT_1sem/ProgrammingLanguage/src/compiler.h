//
// Created by mikhalinho on 12.12.2021.
//

#ifndef PROGRAMMINGLANGUAGE_COMPILER_H
#define PROGRAMMINGLANGUAGE_COMPILER_H

#include "Stack.h"
#include "Set.h"
#include "binary_tree.h"
#include "mystr/mystr.h"
#include "Error_codes.h"

#define SYNTAX_ERR { \
                       error_status = SYNTAX_ERROR;\
                        return NAN;  \
}

#define UNDECLARED {                                    \
                     error_status = UNDECLARED_VARIABLE;\
                        return NAN;                     \
};

#define CONTINUE {                                          \
node->left = binary_tree::Create_node((char*)"STATEMENT");  \
Read_in_tree(node->left, codeblocks.get());                 \
break;                                                      \
}

struct loper {
    char first  = '=';
    char second = ' ';
};


class compiler {
public:
    explicit compiler (const Stack& input_codeblocks, const Set<variable>& vars, const Set<function> fcns)
    :   codeblocks(input_codeblocks),
        variables(vars),
        functions(fcns) {

        Read_in_tree((Node*) tree.Get_root(), codeblocks.get());
    }

    void Read_in_tree(Node* node, codeblock text);

    /*!
     * @method Dump()
     * @brief creates the jpg picture of three using 'Graphviz'
     * @warning don't use the function if you don't have Graphviz.
     * @return int - error code
     */
    int
    Dump();

    void Print_tree_in_file() { tree.print_in_file(); }

    Set<variable> Getvars()         { return variables; }
    Set<function> Getfunctions()    { return functions; }
    binary_tree   GetTree()         { return tree; }

private:
    void _dumpE (const Node* node) const;


    Node* GetLine(const char* str);


    Node*   GetLogical(const char* str);


    Node* GetNumber();


    Node* GetExpression();


    Node* GetLogExpr();


    Node* GetCmp();


    Node* GetMDop();


    Node* GetRadical();


    Node* GetLogBrackets();


    Node* GetLowLogExpr();


    Node* GetBrackets();


    Node* GetPow();


    Node* GetVariable();


    double Require(char c);
    double Require(const char *str, size_t str_size);


    void _dumpV (const Node* node) const;


    binary_tree tree;

private:
    Stack codeblocks;
    char* blockstr = nullptr;

    Set<variable> variables;
    Set<function> functions;

    int error_status = ALL_OK;
};


#endif //PROGRAMMINGLANGUAGE_COMPILER_H
