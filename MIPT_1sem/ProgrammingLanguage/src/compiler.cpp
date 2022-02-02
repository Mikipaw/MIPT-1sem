//
// Created by mikhalinho on 12.12.2021.
//

#include "compiler.h"


void compiler::Read_in_tree(Node* node, codeblock textblock) {
    if (textblock.string == nullptr) return;
    SkipSpaces(&textblock.string);

    const char* text = textblock.string;
    assert(text != nullptr);

    char*   freebuf = new char[LIMITED_SIZE_OF_STRING];
    int     lenstr  = 0;
    int     counter = 0;
    double  number  = 0;

    Node* recursive_node;

    switch (textblock.type) {
        case EMPTY_LINE:
            Read_in_tree(node, codeblocks.get());
            break;

        case EXPRESSION:
            node->type = STAT;
            node->data.statement = (char*) "express";

            node->right = GetLine(text);

            CONTINUE;

        case INITIALISING:
            node->type = STAT;
            node->data.statement = (char*) "INIT";

            text += 9;                  // sizeof "headache"
            //SkipSpaces((char**) text);

            lenstr = 0;
            while (is_alpha(text[lenstr])) {
                freebuf[lenstr] = text[lenstr];
                lenstr++;
            }

            text += lenstr;
            freebuf[lenstr] = '\0';

            assert(variables.search(variable(freebuf)).name != nullptr);

            SkipSpaces((char**) text);
            if (text[0] == '.') {
                node->right = binary_tree::Create_node(VARIABLE);
                node->right->data.statement = new char[LIMITED_SIZE_OF_STRING];
                strcpy(node->right->data.statement, freebuf);
                CONTINUE;
            }

            node->right = binary_tree::Create_node(B_OPERATOR, (char*) "=", nullptr, nullptr);
            RL = new Node;
            RL->type = VARIABLE;
            RL->parent = node->right;
            RL->data.statement = new char[LIMITED_SIZE_OF_STRING];
            strcpy(RL->data.statement, freebuf);


            while (*text != '=') {
                text++;
            }
            text++;

            RR = GetLine(text);

            CONTINUE;

        case ASSIGNMENT:
            node->type = STAT;
            node->data.statement = (char*) "ASSIGNMENT";
            SkipSpaces(((char**)text));
            lenstr = 0;
            while (is_alpha(text[lenstr])) {
                freebuf[lenstr] = text[lenstr];
                lenstr++;
            }
            freebuf[lenstr] = '\0';

            if (!variables.HasElement(variable(freebuf))) throw std::logic_error("Uninitialised variable");

            while (*text != '=') text++;
            text++;
            SkipSpaces(((char**)text));

            node->right = binary_tree::Create_node((char*) "=");

            node->right->type = B_OPERATOR;

            RR = GetLine(text);

            RL = binary_tree::Create_node(VARIABLE, strcpy(new char[LIMITED_SIZE_OF_STRING], freebuf), nullptr, nullptr);
            RL->data.statement = new char[LIMITED_SIZE_OF_STRING];
            strcpy(RL->data.statement, freebuf);

            lenstr = variables.search(variable(freebuf)).number;

            variables.delete_elem(variable(freebuf));
            variables.Add(variable(strcpy(new char[LIMITED_SIZE_OF_STRING], freebuf), RR->data.digit, lenstr));
            CONTINUE

        case WHILE:
            node->type = STAT;
            node->data.statement = (char*) "STATEMENT";

            while (text[0] != '(') text++;
            text++;

            node->right = binary_tree::Create_node((char*) "TRYING");
            RR = GetLogical(text);

            while (text[0] != '{') text++;
            text++;

            RL = binary_tree::Create_node((char*) "STATEMENT");
            Read_in_tree(RL, codeblocks.get());

            CONTINUE

        case IF:
            node->type = STAT;
            node->data.statement = (char*) "STATEMENT";

            while (text[0] != '(') text++;
            text++;

            node->right = binary_tree::Create_node((char*) "MAYBE", nullptr, GetLogical(text));

            while (text[0] != '{') text++;
            text++;

            RL = binary_tree::Create_node((char*) "DECISION",
                                          binary_tree::Create_node(STAT),
                                          binary_tree::Create_node(STAT));

            Read_in_tree(RL->left, codeblocks.get());
            //Read_in_tree(RL->right, codeblocks.get());

            CONTINUE;

        case SCAN:
            node->type = STAT;
            node->data.statement = (char*) "GET";

            while (text[0] != '(') text++;
            text++;
            SkipSpaces((char**) text);

            lenstr = 0;
            while (is_alpha(text[lenstr])) {
                freebuf[lenstr] = text[lenstr];
                lenstr++;
            }
            freebuf[lenstr] = '\0';

            if (!variables.HasElement(variable(freebuf))) throw std::logic_error("Uninitialised variable");

            node->right = binary_tree::Create_node(new char[LIMITED_SIZE_OF_STRING]);
            strcpy(node->right->data.statement, freebuf);

            CONTINUE;

        case PRINT:
            node->type = STAT;
            node->data.statement = (char*) "PMUKMYK";

            while (text[0] != '(') text++;
            text++;
            SkipSpaces((char**) text);

            lenstr = 0;
            if (is_alpha(text[lenstr])) {
                while (is_alpha(text[lenstr])) {
                    freebuf[lenstr] = text[lenstr];
                    lenstr++;
                }
                freebuf[lenstr] = '\0';

                if (!variables.HasElement(variable(freebuf))) throw std::logic_error("Uninitialised variable");

                node->right = binary_tree::Create_node(VARIABLE);
                node->right->data.statement = new char[LIMITED_SIZE_OF_STRING];
                strcpy(node->right->data.statement, freebuf);
            }
            else {
                sscanf(text, "%lf", &number);
                node->right = binary_tree::Create_node(DIGITAL, number);
            }

            CONTINUE;


        case IFELSE:
            node->type = STAT;
            node->data.statement = (char*) "STATEMENT";

            while (text[0] != '(') text++;
            text++;

            node->right = binary_tree::Create_node((char*) "IF", nullptr, GetLogical(text));

            while (text[0] != '{') text++;
            text++;

            RL = binary_tree::Create_node((char*) "DECISION",
                                          binary_tree::Create_node(STAT),
                                          binary_tree::Create_node(STAT));

            Read_in_tree(RL->left,  codeblocks.get());
            Read_in_tree(RL->right, codeblocks.get());

            CONTINUE;

        case DEFINE:
            node->type = STAT;
            node->data.statement = (char*) "STATEMENT";

            text += 5;          // size of "#def "
            sscanf(text, "%s %n", freebuf, &lenstr);

            text += lenstr + 1;
            while ((text)[counter] != '}') {
                if ((text)[counter] == '{')
                    (freebuf + lenstr + 1)[counter] = ' ';
                else (freebuf + lenstr + 1)[counter] = (text)[counter];
                counter++;
            }
            (freebuf + lenstr + 1)[counter] = '\0';


            node->right = binary_tree::Create_node((char*) "DEFINE",
                                                   binary_tree::Create_node(freebuf),
                                                   binary_tree::Create_node(freebuf + lenstr + 1));

            RL->data.statement = new char[LIMITED_SIZE_OF_STRING];
            strcpy(RL->data.statement, freebuf);
            RR->data.statement = new char[LIMITED_SIZE_OF_STRING];
            strcpy(RR->data.statement, freebuf + lenstr + 1);

            CONTINUE;

        case END:
            node->type = STAT;
            node->data.statement = (char*) "END";
            delete[] freebuf;
            return;

        case STOP:
            node->type = STAT;
            node->data.statement = (char*) "BREAK";
            return;

        case CALL:
            node->type = STAT;
            node->data.statement = (char*) "CALL";

            node->right = binary_tree::Create_node((char*) "FUNCTION");

            lenstr = 0;
            while (is_alpha(text[lenstr])) freebuf[lenstr++] = text[lenstr];
            text += lenstr;
            freebuf[lenstr] = '\0';

            assert(functions.search(function(freebuf)).name != nullptr);

            RR = binary_tree::Create_node(freebuf);
            RR->data.statement = new char[LIMITED_SIZE_OF_STRING];
            strcpy(RR->data.statement, freebuf);

            do text++;
            while (text[0] != '(');
            text++;

            counter = functions.search(function(freebuf)).number_of_args;

            RL = binary_tree::Create_node(STAT);
            recursive_node = RL;
            for (int i = 0; i < counter; ++i) {
                if (is_digit(text[0])) {
                    sscanf(text, "%lf", &number);
                    recursive_node->right = binary_tree::Create_node(DIGITAL, number);
                }
                else {
                    lenstr = 0;
                    while (is_alpha(text[lenstr])) freebuf[lenstr++] = text[lenstr];
                    text += lenstr;
                    freebuf[lenstr] = '\0';

                    assert(variables.search(variable(freebuf)).name != nullptr);

                    node->right = binary_tree::Create_node(freebuf);
                    node->right->data.statement = new char[LIMITED_SIZE_OF_STRING];
                    strcpy(node->right->data.statement, freebuf);
                }
                recursive_node = recursive_node->left;

                while (text[0] == ' ' || text[0] == ',') text++;
            }

            CONTINUE

        case MAINE:
            node->type = STAT;
            node->data.statement = (char*) "DEFINE";
            node->right = binary_tree::Create_node((char*) "FUNCTION", binary_tree::Create_node((char*) "problem"), binary_tree::Create_node(STAT));

            Read_in_tree(RR, codeblocks.get());

            CONTINUE;

        case FUNCTION:
            node->type = STAT;
            node->data.statement = (char*) "DEFINE";

            SkipSpaces(((char**)text));
            lenstr = 0;
            while (is_alpha(text[lenstr])) {
                freebuf[lenstr] = text[lenstr];
                lenstr++;
            }
            freebuf[lenstr] = '\0';

            if (!functions.HasElement(function(freebuf))) throw std::logic_error("Undefined function");

            node->right->data.statement = new char[LIMITED_SIZE_OF_STRING];
            node->right = binary_tree::Create_node((char*) "FUNCTION", binary_tree::Create_node(freebuf));
            strcpy(node->right->data.statement, freebuf);

            RR = new Node;
            RR->parent = node->right;
            Read_in_tree(RR, codeblocks.get());

            CONTINUE

        default:
            break;
    }

    delete[] freebuf;
    //Read_in_tree(node, codeblocks.get());
}


void compiler::_dumpE (const Node* node) const {
    if (node == nullptr) return;

    char* tmp_string = (char*) calloc(1, LIMITED_BUFFER_SIZE);

    char* color = nullptr;
    char  str[SHORT_TMP_STRING_SIZE];

    if (node->type == DIGITAL) {
        color = (char*) GOLD;
        sprintf(str, "%lg", DIG);
    }
    else if (node->type == VARIABLE) {
        color = (char*) LIME;
        sprintf(str, "%s", node->data.statement);
    }
    else if (node->type == U_OPERATOR) {
        color = (char*) AQUA;
        switch(OPER) {
            case 'a':
                strcpy(str, "abs");
                break;
                
            case 's':
                strcpy(str, "sin");
                break;
                
            case 'c':
                strcpy(str, "cos");
                break;
                
            case 'l':
                strcpy(str, "log");
                break;

            case RAD:
                strcpy(str, "rad");
                break;

            case CALL:
                strcpy(str, "call");
                break;

            default:
                strcpy(str, "invalid");
        }
    }
    else if (node->type == B_OPERATOR) {
        color = (char*) CRIMSON;
        if (node->data.statement[0] == '>' || node->data.statement[0] == '<') {
            if      (!strncmp(node->data.statement, ">=", 2)) sprintf(str, "me");
            else if (!strncmp(node->data.statement, "<=", 2)) sprintf(str, "le");
            else if (!strncmp(node->data.statement, "==", 2)) sprintf(str, "ee");
            else if (!strncmp(node->data.statement, "!=", 2)) sprintf(str, "ne");
            else if (!strncmp(node->data.statement, ">", 1))  sprintf(str, "m");
            else if (!strncmp(node->data.statement, "<", 1))  sprintf(str, "l");
        }
        else sprintf(str, "%s", node->data.statement);
    }
    else if (node->type == STAT) {
        color = (char*) LBLUE;
        sprintf(str, "%s", node->data.statement);
    }

    sprintf(tmp_string,
            "node%p[ style = \"filled, rounded\", fillcolor = \"%s\"]"
            "node%p [label=\"<f0> name (%s)|<f1> address (%p)|<f2> left (%p)|<f3> right (%p)\"];\n",
            node, color, node, str, node, node->left, node->right);

    strcat(blockstr, tmp_string);

    if (node->left  != nullptr) _dumpE(node->left);
    if (node->right != nullptr) _dumpE(node->right);

    free(tmp_string);

}

void compiler::_dumpV (const Node* node) const {
    if (node != nullptr) {
        char* temp_string = (char*) calloc(1, LIMITED_BUFFER_SIZE);
        if (node->right != nullptr) {
            sprintf(temp_string, "node%p:f3 -> node%p:f0;\n", node, node->right);
            strcat(blockstr, temp_string);
            _dumpV(node->right);
        }

        if (node->left  != nullptr) {
            sprintf(temp_string, "node%p:f2 -> node%p:f0;\n", node, node->left);
            strcat(blockstr, temp_string);
            _dumpV(node->left);
        }

        free(temp_string);
    }

}

int compiler::Dump() {
    FILE* Graph = fopen("Graph.dot", "wb");
    if(Graph == nullptr) fprintf(stderr, "Error opening file!\n");

    blockstr = (char*) calloc(codeblocks.Get_Size(), BUFFER_SIZE);

    const char* DEFAULT_TEXT = "digraph G{\n"
                               "edge [color = \"darkgreen\"];\n"
                               "rankdir = \"LR\";\n"
                               "node [shape = record];\n"
                               "node [color = \"#000000\", shape = record];\n";
    strcat(blockstr, DEFAULT_TEXT);

    _dumpE(tree.Get_root());
    _dumpV(tree.Get_root());

    fputs(blockstr, Graph);
    fputs("}\n", Graph);

    fclose(Graph);

    char*  command = (char*) calloc(2, 32);
    strcpy (command, DOT);
    strcat (command, OUTPUT_FILE_NAME);

    system (command);

    char* command2 = (char*) calloc(2, 32);
    strcat(command2, "eog ");
    strcat(command2, OUTPUT_FILE_NAME);
    system (command2);

    free(command);

    return ZERO;
}


Node* compiler::GetLine(const char *str) {
    blockstr = (char*) str;

    Node* value = GetExpression();

    //if (std::isnan(Require("...", 3)) && std::isnan(Require(')'))) SYNTAX_ERR
    return value;
}


Node* compiler::GetLogical(const char *str) {
    blockstr = (char*) str;

    Node* value = GetLowLogExpr();

    return value;
}


Node* compiler::GetNumber() {
    double value = 0;

    if (is_alpha(*blockstr)) {
        char* varname = new char[LIMITED_SIZE_OF_STRING];
        int lenstr = 0;

        while (is_alpha(blockstr[lenstr])) {
            varname[lenstr] = blockstr[lenstr];
            lenstr++;
        }
        varname[lenstr] = '\0';

        if (variables.HasElement(variable(varname))) {
            blockstr += lenstr;

            Node* new_node = binary_tree::Create_node(VARIABLE);
            new_node->data.statement = new char[LIMITED_SIZE_OF_STRING];
            strcpy(new_node->data.statement, varname);

            return new_node;
        }
    }

    const char* copy_str = blockstr;

    while ('0' <= *blockstr && *blockstr <= '9') {
        value = value * 10 + (*blockstr - '0');
        blockstr++;
    }

    if (*blockstr == '.') {
        if (!('0' <= *blockstr && *blockstr <= '9')) if (*blockstr == '.') return binary_tree::Create_node(DIGITAL, value);
        int after_pointer = 1;
        while ('0' <= *blockstr && *blockstr <= '9') {
            value = value + (*blockstr - '0') * pow(10, -after_pointer);
            blockstr++;
        }
    }

    if (copy_str == blockstr) return nullptr;

    return binary_tree::Create_node(DIGITAL, value);
}


Node* compiler::GetLowLogExpr() {
    Node* lhs = GetLogExpr();
    //if (error_status) throw std::logic_error("Syntax error!");

    while (*blockstr == '|' && blockstr[1] == '|') {
        blockstr += 2;

        Node* rhs = GetLogExpr();
        if (error_status) throw std::logic_error("Syntax error!");

        Node* result = binary_tree::Create_node((char*) "or", lhs, rhs);
        result->type = B_OPERATOR;

        return result;
    }

    return lhs;
}

Node* compiler::GetExpression() {
    Node* lhs = GetMDop();

    while (*blockstr == '+' || *blockstr == '-') {
        char oper = *blockstr;
        blockstr++;

        Node* rhs = GetMDop();

        if (oper == '+')    lhs = binary_tree::Create_node(B_OPERATOR, (char*) "+", lhs, rhs);
        else                lhs = binary_tree::Create_node(B_OPERATOR, (char*) "-", lhs, rhs);
    }

    return lhs;
}


Node* compiler::GetLogExpr() {
    Node* lhs = GetCmp();
    //if (error_status) throw std::logic_error("Syntax error!\n");

    while (*blockstr == '&' && blockstr[1] == '&') {
        blockstr += 2;

        Node* rhs = GetCmp();
        if (error_status) throw std::logic_error("Syntax error!\n");

        lhs = binary_tree::Create_node((char*) "&&", lhs, rhs);
        lhs->type = B_OPERATOR;

        return lhs;
    }

    return lhs;
}


Node* compiler::GetMDop() {
    Node* lhs = GetPow();

    while (*blockstr == '*' || *blockstr == '/') {
        char oper = *blockstr;
        blockstr++;

        Node* rhs = GetPow();

        if (oper == '*')    lhs = binary_tree::Create_node(B_OPERATOR, (char*) "*", lhs, rhs);
        else                lhs = binary_tree::Create_node(B_OPERATOR, (char*) "/", lhs, rhs);
    }

    return lhs;
}


Node* compiler::GetPow() {
    Node* lhs = GetRadical();

    while (*blockstr == '^') {
        blockstr++;

        Node* rhs = GetRadical();
        lhs = binary_tree::Create_node(B_OPERATOR, (char*) "^", lhs, rhs);
    }

    return lhs;
}

Node* compiler::GetCmp() {
    Node* lhs = GetLogBrackets();

    while (*blockstr == '=' && blockstr[1] == '='
           || *blockstr == '!' && blockstr[1] == '='
           || *blockstr == '>' && blockstr[1] == '='
           || *blockstr == '<' && blockstr[1] == '='
           || *blockstr == '>' || blockstr[0] == '<') {
        loper oper = {blockstr[0], blockstr[1]};
        blockstr++;
        if (*blockstr == '=') blockstr++;

        Node* rhs = GetLogBrackets();

        if (oper.second == ' ') {
            if (oper.first == '>') return binary_tree::Create_node(B_OPERATOR, (char*) ">", lhs, rhs);
            else                   return binary_tree::Create_node(B_OPERATOR, (char*) "<", lhs, rhs);
        }
        else if (oper.second == '=') {
            if (oper.first == '>') return binary_tree::Create_node(B_OPERATOR, (char*) ">=", lhs, rhs);
            if (oper.first == '<') return binary_tree::Create_node(B_OPERATOR, (char*) "<=", lhs, rhs);;
            if (oper.first == '=') return binary_tree::Create_node(B_OPERATOR, (char*) "==", lhs, rhs);
            if (oper.first == '!') return binary_tree::Create_node(B_OPERATOR, (char*) "!=", lhs, rhs);
        }
    }

    return lhs;
}


Node* compiler::GetRadical() {
    if (*blockstr == 'r') {
        if (!strncmp(blockstr, "rad", 3)) {
            blockstr += 3;
            Node* lhs = binary_tree::Create_node(U_OPERATOR, RAD, nullptr, GetExpression());

            return lhs;
        }
        else return nullptr;
    }
    else return GetBrackets();
}


Node* compiler::GetBrackets() {
    if (*blockstr == '(') {
        blockstr++;
        Node* lhs = GetExpression();
        blockstr++;

        return lhs;
    } else
        return GetNumber();
}


Node* compiler::GetLogBrackets() { //not done
    if (*blockstr == '(') {
        blockstr++;
        Node* lhs = GetLowLogExpr();

        if (*blockstr == ')') blockstr++;
        return lhs;
    }
    else return GetExpression();
}


double compiler::Require(char c) {
    if (*blockstr == c) blockstr++;
    else SYNTAX_ERR

    return 0;
}

double compiler::Require(const char *str, size_t str_size) {
    for (int i = 0; i < str_size; ++i) {
        if (*blockstr != str[i]) SYNTAX_ERR
        blockstr++;
    }

    return 0;
}