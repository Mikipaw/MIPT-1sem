//
// Created by mikhalinho on 17.12.2021.
//

#include "Backend.h"

int Translator::read_tree() {
    input = fopen("Tree.txt",    "rb");
    size_t fsize = Size_of_file(input);
    input_text = text_from_file(input, fsize);
    fclose(input);

    return 0;
}


int Translator::Translate() {
    write_node(tree.Get_root());

    return 0;
}


int Translator::write_node(const Node* node) {
    int index = 0;
    double number = 0;
    variable cur_var;
    function cur_func;

    switch (node->type) {
        case DIGITAL:
            fprintf(output, "PUSH %.2lf\n", DIG);
            break;

        case VARI:
            cur_var = variables.search(variable(node->data.statement));
            index = MEMORY_FOR_VARS + cur_var.number;
            fprintf(output, "PUSH [%d]\n", index);

            break;

        case U_OPERATOR:
            if (OPER != RAD) write_node(node->left);
            else write_node(node->right);

            switch (OPER) {
                case SIN:
                    fprintf(output, "SINUS\n");
                    break;

                case COS:
                    fprintf(output, "COS\n");
                    break;

                case LN:
                    fprintf(output, "LN\n");
                    break;

                case RAD:
                    fprintf(output, "SQRT\n");
                    break;

                    }

            break;

        case B_OPERATOR:
            write_node(node->left);
            write_node(node->right);


            if (!strncmp(node->data.statement, ">=", 2)) {
                fprintf(output, "JAE :%d\n", mark);
                mark++;
            }
            else if (!strncmp(node->data.statement, "<=", 2)) {
                fprintf(output, "JBE :%d\n", mark);
                mark++;
            }
            else if (!strncmp(node->data.statement, "==", 2)) {
                fprintf(output, "JE :%d\n", mark);
                mark++;
            }
            else if (!strncmp(node->data.statement, "!=", 2)) {
                fprintf(output, "JNE :%d\n", mark);
                mark++;
            }
            else if (!strncmp(node->data.statement, ">", 1)) {
                fprintf(output, "JA :%d\n", mark);
                mark++;
            }
            else if (!strncmp(node->data.statement, "<", 1)) {
                fprintf(output, "JB :%d\n", mark);
                mark++;
            }
            else if (!strncmp(node->data.statement, "+", 1)) {
                fprintf(output, "ADD\n");
                mark++;
            }
            else if (!strncmp(node->data.statement, "-", 1)) {
                fprintf(output, "SUB\n");
                mark++;
            }
            else if (!strncmp(node->data.statement, "*", 1)) {
                fprintf(output, "MUL\n");
                mark++;
            }
            else if (!strncmp(node->data.statement, "/", 1)) {
                fprintf(output, "DIV\n");
                mark++;
            }
            else if (!strncmp(node->data.statement, "^", 1)) {
                fprintf(output, "POW\n");
                mark++;
            }
            else if (!strncmp(node->data.statement, "=", 1)) {
                cur_var = variables.search((variable(node->left->data.statement)));
                index = cur_var.number + MEMORY_FOR_VARS;
                fprintf(output, "POP [%d]\nPOP\n", index);
            }

            break;

        case STAT:
            switch (node->data.statement[0]) {
                case 'F':           //Function
                    cur_func = functions.search(function(node->left->data.statement));
                    if (!str_equal(node->left->data.statement, "problem")) fprintf(output, "%d:\n", cur_func.number);
                    write_node(node->right);
                    if (!str_equal(node->left->data.statement, "problem")) fprintf(output, "RET\n");

                    break;

                case 'I':       //Initialization
                    if (node->data.statement[1] == 'N') {
                        write_node(node->right);
                        write_node(node->left);
                        break;
                    }

                case 'M':                   //maybe
                    if (node->data.statement[2] == 'E') {
                        write_node(node->left);
                        index = mark;

                        write_node(RR);
                        fprintf(output, "JMP :%d\n%d:\n", index, index - 1);
                        write_node(RL);

                        fprintf(output, "%d:\n", index);
                        mark++;
                    }
                    else {
                        write_node(node->right);
                        index = mark;
                        fprintf(output, "JMP :%d\n%d:\n", index, index - 1);

                        write_node(LL);
                        fprintf(output, "%d:\n", index);
                        mark++;
                    }

                    break;

                case 'T':       //while (trying)
                    fprintf(output, "%d:\n", mark);
                    write_node(node->left);

                    write_node(node->right);
                    break;

                case 'G':       //get (scan)
                    fprintf(output, "IN\n");
                    cur_var = variables.search(variable(node->right->data.statement));
                    index = MEMORY_FOR_VARS + cur_var.number;

                    fprintf(output, "POP [%d]\n", index);
                    write_node(node->left);
                    break;

                case 'P':           //print
                    if (node->right->type == VARIABLE) {
                        cur_var = variables.search(variable(node->right->data.statement));
                        index = MEMORY_FOR_VARS + cur_var.number;

                        fprintf(output, "PUSH [%d]\n", index);

                    }
                    else fprintf(output, "PUSH %.2lf\n", node->right->data.digit);

                    fprintf(output, "OUT\n");

                    write_node(node->left);
                    break;

                case 'A':       //Ass
                    if (RR != nullptr){
                        cur_var = variables.search(variable(RL->data.statement));
                        index = cur_var.number + MEMORY_FOR_VARS;
                        write_node(RR);
                        fprintf(output, "POP [%d]\n", index);
                    }
                    else break;
                    write_node(node->left);

                    break;

                case 'r':
                    write_node(node->right);
                    fprintf(output, "SQRT\n");
                    break;

                case 'S':       //statement
                case 'D':       //define
                    if (node->right != nullptr) write_node(node->right);
                    if (node->left  != nullptr) write_node(node->left);
                    break;

                case 'E':       //end
                    fprintf(output, "HLT");
                    break;

                default:
                case 'B':       //break
                    break;
            }

            break;

        case EMPTY_LINE:
            break;

        default:
            break;
            }

    return 0;
}
