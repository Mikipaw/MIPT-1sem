//
// Created by mikhalinho on 23.11.2021.
//

#include <cassert>
#include <cstdlib>
#include <cstring>

#include "differetiator.h"


void Differentiator::destroy_tree_(Node* node) {
    if(node != nullptr){
        destroy_tree_(node->left);
        destroy_tree_(node->right);
        delete node;
    }
}

int Differentiator::get_height_(const Node *node) const{
    if (node == nullptr) return 0;

    int lHeight = get_height_(node->left);
    int rHeight = get_height_(node->right);

    if(lHeight > rHeight) return (lHeight + 1);
    else return (rHeight + 1);
}

Differentiator::Differentiator(const char* input) {
    root = new Node;
    FILE* database = fopen(input, "rb");
    size_t size_of_file = Size_of_file(database);
    size_t number_of_lines = 0;
    text = text_from_file(database, size_of_file, &number_of_lines);

    size = (int) number_of_lines;
    Read_in_tree(root);

    fclose(database);
}


void Differentiator::Read_in_tree(Node* node) {
    assert(text != nullptr);

    while (text[0] == ' ') text++;

    if (text[0] == ')') {
        text++;
        Read_in_tree(node->parent);
    }
    if (text[0] == '\0') return;
    if (text[0] == '(') {
        text++;
        size += 3;
        node->left = new Node;
        node->left->parent = node;
        Read_in_tree(node->left);
    }

    if (is_digit(text[0])) {
        char* ptr;

        DIG = strtod(text, &ptr);
        while (is_digit(text[0])) text++;

        node->type = DIGITAL;
        if (node != root) {
            if (node->parent->type == U_OPERATOR) Read_in_tree(node->parent->parent);
            else if (node->parent != nullptr) Read_in_tree(node->parent);
        }
    }

    else {
        int is_oper = oper(node);
        if (is_oper == B_OPERATOR) {
            node->right = new Node;
            node->right->parent = node;
            Read_in_tree(node->right);
        }
        else if (is_oper == U_OPERATOR) {
            node->left = new Node;
            node->left->parent = node;
            Read_in_tree(node->left);
        }
        else if (isvar(text[0])) {
            sscanf(text++, "%c", &VAR);
            node->type = VARIABLE;
        }
        else size += 2;

        if (node != root) {
            if (node->parent->type == U_OPERATOR) Read_in_tree(node->parent->parent);
            else if (node->parent != nullptr) Read_in_tree(node->parent);
        }
    }
}

int Differentiator::oper(Node* node) {
    if(text[0] == ' ') text++;

    switch (text[0]) {
        case '+':
            text++;
            node->type      = B_OPERATOR;
            OPER = ADD;
            break;

        case '-':
            text++;
            node->type      = B_OPERATOR;
            OPER = SUB;
            break;

        case '*':
            text++;
            node->type      = B_OPERATOR;
            OPER = MUL;
            break;

        case '/':
            text++;
            node->type      = B_OPERATOR;
            OPER = DIV;
            break;

        case '%':
            text++;
            node->type      = B_OPERATOR;
            OPER = MOD;
            break;

        case '^':
            text++;
            node->type      = B_OPERATOR;
            OPER = POW;
            break;

        case 'a':
            if (text[1] != 'b' || text[2] != 's') break;

            text += 3;
            node->type      = U_OPERATOR;
            OPER = ABS;
            break;

        case 's':
            if (text[1] != 'i' || text[2] != 'n') break;

            text += 3;
            node->type      = U_OPERATOR;
            OPER = SIN;
            break;

        case 'c':
            if (text[1] != 'o' || text[2] != 's') break;

            text += 3;
            node->type      = U_OPERATOR;
            OPER = COS;
            break;
        case 'l':
            if (text[1] != 'n') break;

            text += 2;
            node->type      = U_OPERATOR;
            OPER = LN;
            break;

        default:
            return 0;

    }
    return node->type;
}

char* strchar(char* buffer, char sym) {
    char* c = buffer;
    while (*c != sym) {
        c++;
        if (c == nullptr || *c == '\0') return c;
    }

    return c;
}

void Differentiator::_dumpE (Node* node) const {
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
        sprintf(str, "%c", VAR);
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
            default:
                strcpy(str, "invalid");
        }
    }
    else if (node->type == B_OPERATOR) {
        color = (char*) CRIMSON;
        sprintf(str, "%c", OPER);
    }

    sprintf(tmp_string,
            "node%p[ style = \"filled, rounded\", fillcolor = \"%s\"]"
            "node%p [label=\"<f0> name (%s)|<f1> address (%p)|<f2> left (%p)|<f3> right (%p)\"];\n",
            node, color, node, str, node, node->left, node->right);

    strcat(f_round_str, tmp_string);

    if (node->left  != nullptr) _dumpE(node->left);
    if (node->right != nullptr) _dumpE(node->right);

    free(tmp_string);

}

void Differentiator::_dumpV (Node* node) const {
    if (node != nullptr) {
        char* temp_string = (char*) calloc(15, 32);
        if (node->right != nullptr) {
            sprintf(temp_string, "node%p:f3 -> node%p:f0;\n", node, node->right);
            strcat(f_round_str, temp_string);
            _dumpV(node->right);
        }

        if (node->left  != nullptr) {
            sprintf(temp_string, "node%p:f2 -> node%p:f0;\n", node, node->left);
            strcat(f_round_str, temp_string);
            _dumpV(node->left);
        }

        free(temp_string);
    }

}

int Differentiator::Dump() {
    if (verification()) return verification();

    FILE* Graph = fopen("Graph.dot", "wb");
    if(Graph == nullptr) fprintf(stderr, "Error opening file!\n");

    f_round_str = (char*) calloc(size, BUFFER_SIZE);

    const char* DEFAULT_TEXT = "digraph G{\n"
                               "edge [color = \"darkgreen\"];\n"
                               "rankdir = \"LR\";\n"
                               "node [shape = record];\n"
                               "node [color = \"#000000\", shape = record];\n";
    strcat(f_round_str, DEFAULT_TEXT);

    _dumpE(root);
    _dumpV(root);

    fputs(f_round_str, Graph);
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

    //free(f_round_str);
    if (verification()) return verification();

    return ALL_OK;
}


int Differentiator::check (Node* node) const{
    if (node == nullptr) return ALL_OK;

    //if (node->type == DIGITAL || node->type == VARIABLE)    assert(node->left == nullptr && node->right == nullptr);
    if (node->type == B_OPERATOR)                           assert(node->left != nullptr && node->right != nullptr);
    if (node->type == U_OPERATOR)                           assert(node->left != nullptr && node->right == nullptr);

    int error_code = ALL_OK;
    error_code = check(node->left);
    if (error_code) return error_code;

    error_code = check(node->right);
    if (error_code) return error_code;

    return ALL_OK;
}

Node* Differentiator::copy_subtree (const Node* node) {
    if (node == nullptr) return nullptr;

    Node* new_root = new Node;

    new_root->type = node->type;
    new_root->data = node->data;

    new_root->left  = copy_subtree(node->left);
    new_root->right = copy_subtree(node->right);

    return new_root;

}

Node* Differentiator::_differentiate(Node *node) {
    switch (node->type) {
        case DIGITAL:
            return Create_node(DIGITAL, 0);

        case VARIABLE:
            if (VAR != 'x') return Create_node(DIGITAL, 0);
            return C;

        case B_OPERATOR:
            switch (OPER) {
                case ADD:
                    return dADD;

                case SUB:
                    return dSUB;

                case MUL:
                    if ( is_const(node->left) && !is_const(node->right)) return Create_node(B_OPERATOR, MUL, L, dR);
                    if (!is_const(node->left) &&  is_const(node->right)) return Create_node(B_OPERATOR, MUL, dL, R);
                    return dMUL;

                case DIV:
                    if ( is_const(node->left) && !is_const(node->right)) return Create_node(B_OPERATOR, DIV, L, dR);
                    if (!is_const(node->left) &&  is_const(node->right)) return dCDIV;
                    return dDIV;

                case POW:
                    if (is_const(node->left)  && is_const(node->right))  return ZERO;

                    if (!is_const(node->left) && is_const(node->right))  return dVPC;
                    if (is_const(node->left)  && !is_const(node->right)) return dCPV;

                    if (!is_const(node->left) && !is_const(node->right)) return dVPV;

                default:
                    return nullptr;
            }

        case U_OPERATOR:
            switch (OPER) {
                case SIN:
                    return dSIN;

                case COS:
                    return dCOS;

                case LN:
                    return dLOG;

                default:
                    return nullptr;
            }
        default:
            fprintf(stderr, "Error in differentiation process...\n"
                            "Can't take the differential.\n");
            return nullptr;
    }
}

Node* Differentiator::New_node(Node* node, int direction, int new_type, Node* left_child, Node* right_child) {
    if (direction == LEFT) {
        if (node->left != nullptr) return nullptr;

        node->left = new Node;
        node->left->parent = node;
        node->left->type = new_type;

        if (left_child  != nullptr) LL  = left_child;
        if (right_child != nullptr) LR = right_child;

        return node->left;
    }
    else if (direction == RIGHT) {
        if (node->right != nullptr) return nullptr;

        node->right = new Node;
        node->right->parent = node;
        node->right->type = new_type;

        if (left_child  != nullptr) RL  = left_child;
        if (right_child != nullptr) RR = right_child;

        return node->right;
    }

    return nullptr;
}

Node* Differentiator::Create_node(int new_type, double new_data, Node* left_child, Node* right_child) {
    Node* node = new Node;

    node->type = new_type;

    switch (new_type) {
        case DIGITAL:
            DIG = new_data;
            break;
        case VARIABLE:
            VAR = (char) new_data;
            break;
        case U_OPERATOR:
        case B_OPERATOR:
            OPER = (int) new_data;
            break;
        default:
            break;
    }

    if (left_child  != nullptr) node->left  = left_child;
    if (right_child != nullptr) node->right = right_child;

    return node;
}

bool Differentiator::is_const(Node* node) const {
    bool leftres  = false;
    bool rightres = false;

    if (node->type == B_OPERATOR) {
        if (node->left->type  == B_OPERATOR || node->left->type  == U_OPERATOR) leftres  = is_const(node->left);
        if (node->right->type == B_OPERATOR || node->right->type == U_OPERATOR) rightres = is_const(node->right);
    }

    if (node->type == U_OPERATOR)
        if (node->left->type == B_OPERATOR || node->left->type == U_OPERATOR) leftres = is_const(node->left);


    if (node->type == VARIABLE) if (VAR == 'x')          return false;
    if (node->type == DIGITAL || node->type == VARIABLE) return true;

    return (leftres || rightres);
}

void Differentiator::Tree_To_TeX(const Node* node) {
    fprintf(LatexFile, "\\begin{dmath}\n\t");
    _dump_to_tex(node);
    fprintf(LatexFile, "\n\\end{dmath}\n");
}


void Differentiator::destroy_tree() {
    destroy_tree_(root);

    fclose(LatexFile);

    system("latexmk -f -silent -pdf Tex/Dump.tex Tex/Dump.pdf");
}

int Differentiator::Dump_to_TeX() {
    fprintf(LatexFile, R"(\documentclass[a4paper,12pt]{article}
                                    \usepackage[T2A]{fontenc}
                                    \usepackage[utf8]{inputenc}
                                    \usepackage[english, russian]{babel}
                                    \usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools}
                                    \usepackage{wasysym}
                                    \usepackage{pgfplots}
                                    \pgfplotsset{compat = 1.9}
                                    \usepackage{graphicx}
                                    \usepackage[unicode, pdftex]{hyperref}
                                    \usepackage[normalem]{ulem}
                                    \usepackage{ulem}
                                    \usepackage{breqn}
                                    \begin{center}
                                    \t{\large \textbf{Differentiator}}
                                    \end{center}
                                    \begin{center}
                                    \t{\large \textit{\textbf{Mikhail Pavlov},\\
                                    Radio engineering and Computer Science,\\
                                    Moscow Institute of Physics and Technologies}}
                                    \end{center}
                                    \newpage)");

    fprintf(LatexFile, "\\section*{\\textbf{Getting the partial}}\n"
                       "Original expression (looks so easy to get a partial):\n");

    int opt = 8;
    while (!optimized) {
        Tree_To_TeX(root);
        fprintf(LatexFile, "%s", phrases[(opt--)%10]);
        optimize();
    }


    Node* new_node = differentiate();
    optimized = false;

    kill_children(root);
    root = new_node;

    fprintf(LatexFile, "\n\n\\vspace{1cm} \nLet's get the derivative!\n");

    int i = 0;
    while (!optimized) {
        Tree_To_TeX(root);
        fprintf(LatexFile, "%s", phrases[(i++)%10]);
        optimize();
    }

    fprintf(LatexFile, "\n \\end{document}");

    return 0;
}

int Differentiator::_dump_to_tex(const Node* node) {
    if (node == nullptr) return 0;
    switch (node->type) {
        case U_OPERATOR:
            if (node->left == nullptr) return 0;
            switch (OPER) {
                case SIN:
                    if   (node->left->type == VARIABLE || node->left->type == DIGITAL) fprintf(LatexFile, " sin");
                    else fprintf(LatexFile, " sin\\left(");
                    break;

                case COS:
                    if   (node->left->type == VARIABLE || node->left->type == DIGITAL) fprintf(LatexFile, " cos");
                    else fprintf(LatexFile, " cos\\left(");
                    break;

                case LN:
                    if   (node->left->type == VARIABLE || node->left->type == DIGITAL) fprintf(LatexFile, " ln");
                    else (fprintf(LatexFile, " ln\\left("));
                    break;
            }
            _dump_to_tex(node->left);
            if   (node->left->type == U_OPERATOR || node->left->type == B_OPERATOR) fprintf(LatexFile, "\\right) ");
            break;

        case B_OPERATOR:
            if (node->left == nullptr || node->right == nullptr) return 0;
            switch (OPER) {
                case DIV:
                    fprintf(LatexFile, "\\frac{");
                    _dump_to_tex(node->left);

                    fprintf(LatexFile, "}{");

                    _dump_to_tex(node->right);
                    fprintf(LatexFile, "} ");
                    break;

                case POW:
                    if (node->left->type != VARIABLE && node->left->type != DIGITAL) fprintf(LatexFile, " \\left(");
                    _dump_to_tex(node->left);

                    if (node->left->type != VARIABLE && node->left->type != DIGITAL) fprintf(LatexFile, "\\right)^{");
                    else fprintf(LatexFile, "^{");

                    _dump_to_tex(node->right);
                    fprintf(LatexFile, "} ");
                    break;

                case MUL:
                    _dump_to_tex(node->left);
                    fprintf(LatexFile, " \\cdot ");
                    _dump_to_tex(node->right);
                    break;

                case ADD:
                case SUB:
                     if (node != root) fprintf(LatexFile, " \\left(");

                     _dump_to_tex(node->left);
                    fprintf(LatexFile, " %c ", OPER);
                    _dump_to_tex(node->right);

                    if (node != root) fprintf(LatexFile, "\\right) ");
                    break;

                default:
                    fprintf(stderr, "Invalid expression tree!\n");
                    return INVALID_EXPRESSION;
            }
            break;

        case VARIABLE:
            fprintf(LatexFile, "%c", VAR);
            break;

        case DIGITAL:
            fprintf(LatexFile, "%lg", DIG);
            break;

        default:
            fprintf(stderr, "Invalid type of node %p\n", node);
            return INVALID_TYPE;
    }

    return ALL_OK;
}

int Differentiator::_optimize(Node *node) {
    switch (node->type) {
        case VARIABLE:
            return NOTHING;

        case DIGITAL:
            if (DIG == 0) return EQUAL_ZERO;
            if (DIG == 1) return EQUAL_ONE;
            break;

        case U_OPERATOR:
            switch (OPER) {
                case LN:
                    if (node->left->type == DIGITAL) {
                        optimized = false;

                        node->type = DIGITAL;
                        DIG = log(node->left->data.digit);

                        destroy_tree_(LL);
                        destroy_tree_(LR);

                        node->left = nullptr;
                        break;
                    }
                    else if (node->left->type == U_OPERATOR || node->left->type == B_OPERATOR) _optimize(node->left);
                    return NOTHING;

                case SIN:
                    if (node->left->type == DIGITAL) {
                        optimized = false;

                        node->type = DIGITAL;
                        DIG = sin(DIG);

                        destroy_tree_(LL);
                        destroy_tree_(LR);

                        node->left = nullptr;
                        break;
                    }
                    else if (node->left->type == U_OPERATOR || node->left->type == B_OPERATOR) _optimize(node->left);
                    return NOTHING;

                case COS:
                    if (node->left->type == DIGITAL) {
                        optimized = false;

                        node->type = DIGITAL;
                        DIG = cos(DIG);

                        destroy_tree_(LL);
                        destroy_tree_(LR);

                        node->left = nullptr;
                        break;
                    }
                    else if (node->left->type == U_OPERATOR || node->left->type == B_OPERATOR) _optimize(node->left);
                    return NOTHING;

                default: return INVALID_NODE;
            }

        case B_OPERATOR:
            if (node->left == nullptr || node->right == nullptr) return 0;
            switch (OPER) {
                case SUB:
                case ADD:
                    if (OPER == SUB)
                        if (Is_Equal(L, R)) {
                            node->type = DIGITAL;
                            DIG = 0;

                            kill_children(node);

                            optimized = false;
                            break;
                        }

                    ISLZERO {
                        optimized = false;

                        if (node->data.oper == SUB) {
                            node->data.oper = MUL;
                            node->left->data.digit = -1;
                            break;
                        }

                        node->type = node->right->type;
                        node->data = node->right->data;

                        if (node->type == B_OPERATOR) {
                            node->right = RR;
                            node->left = RL;
                        }
                        else if (node->type == U_OPERATOR) {
                            node->left = RL;
                            node->right = nullptr;
                        }
                        else {
                            node->left = nullptr;
                            node->right = nullptr;
                        }

                        break;
                    }

                    ISRZERO {
                        optimized = false;

                        node->type = node->left->type;
                        node->data = node->left->data;

                        if (node->type == B_OPERATOR) {
                            node->right = LR;
                            node->left = LL;
                        }
                        else if (node->type == U_OPERATOR) {
                            node->right = nullptr;
                            node->left = LL;
                        }
                        else {
                            node->left = nullptr;
                            node->right = nullptr;
                        }

                        break;
                    }

                    ISDIGDIG {
                        optimized = false;

                        node->type = DIGITAL;
                        if (OPER == ADD) DIG = node->left->data.digit + node->right->data.digit;
                        if (OPER == SUB) DIG = node->left->data.digit - node->right->data.digit;

                        break;
                    }

                    if (node->left->type  == U_OPERATOR || node->left->type  == B_OPERATOR) _optimize(node->left);
                    if (node->right->type == B_OPERATOR) _optimize(node->right);

                    break;

                case MUL:
                case DIV:
                    if (OPER == DIV)
                        if (Is_Equal(node->left, node->right)) {
                            node->type = DIGITAL;
                            DIG = 1;

                            kill_children(node);

                            optimized = false;
                            break;
                        }

                    ISLZERO {
                        optimized = false;

                        node->type = DIGITAL;
                        DIG = 0;

                        kill_children(node);
                        break;
                    }

                    ISRZERO {
                        optimized = false;

                        if (OPER == DIV) return DIV_ZERO;

                        node->type = DIGITAL;
                        DIG = 0;

                        kill_children(node);
                        break;
                    }

                    if (LONE && OPER == MUL) {
                        optimized = false;

                        node->left = RL;
                        node->data = node->right->data;
                        node->type = node->right->type;

                        Node* tmp_node = RR;

                        node->right = tmp_node;

                        break;
                    }

                    if (VARVAR && OPER == DIV) {
                        if (node->left->data.variable != node->right->data.variable) break;
                        node->right = nullptr;
                        node->left = nullptr;
                        node->type = DIGITAL;
                        DIG = 1;

                        break;
                    }

                    if (RONE) {
                        optimized = false;

                        node->right = LR;
                        node->data = node->left->data;
                        node->type = node->left->type;

                        Node* tmp_node = LL;

                        node->left = tmp_node;
                        break;
                    }

                    if (VARVAR) {
                        optimized = false;

                        node->type = DIGITAL;
                        if (OPER == MUL) DIG = node->left->data.digit * node->right->data.digit;
                        if (OPER == DIV) DIG = node->left->data.digit / node->right->data.digit;

                        kill_children(node);
                        break;
                    }

                    if (node->left->type  == U_OPERATOR || node->left->type  == B_OPERATOR) _optimize(node->left);
                    if (node->right->type == B_OPERATOR) _optimize(node->right);

                    break;

                case POW:
                    ISLZERO {
                        optimized = false;

                        node->type = node->right->type;
                        DIG = 0;

                        kill_children(node);
                        break;
                    }

                    if (RZERO || LONE) {
                        optimized = false;

                        node->type = DIGITAL;
                        DIG = 1;

                        kill_children(node);
                        break;
                    }

                    if (RONE) {
                        optimized = false;

                        node->right = LR;
                        node->data = node->left->data;
                        node->type = node->left->type;

                        Node* tmp_node = LL;

                        node->left = tmp_node;

                        break;
                    }

                    ISDIGDIG {
                        optimized = false;

                        node->type = DIGITAL;
                        DIG = pow(node->left->data.digit, node->right->data.digit);

                        kill_children(node);
                        break;
                    }

                    if (node->left->type  == U_OPERATOR || node->left->type  == B_OPERATOR) _optimize(node->left);
                    if (node->right->type == B_OPERATOR) _optimize(node->right);

                    break;
            }
    }

    return NOTHING;
}


bool Is_Equal(const Node* root_left, const Node* root_right) {
    if (root_left == nullptr && root_right != nullptr || root_left != nullptr && root_right == nullptr) return false;

    if (root_right != nullptr && root_left != nullptr) {
        if (!Is_Equal(root_left->left, root_right->left))   return false;
        if (root_left->type != root_right->type)            return false;

        switch (root_left->type) {
            case DIGITAL:
                if (root_left->data.digit != root_right->data.digit) return false;
                break;

            case VARIABLE:
                if (root_left->data.variable != root_right->data.variable) return false;
                break;

            case U_OPERATOR:
                if (root_left->data.oper != root_right->data.oper) return false;
                if (!Is_Equal(root_left->left, root_right->left))  return false;
                break;

            case B_OPERATOR:
                if (root_left->data.oper != root_right->data.oper)  return false;
                if (!Is_Equal(root_left->left,  root_right->left))  return false;
                if (!Is_Equal(root_left->right, root_right->right)) return false;
                break;

        }


    }

    return true;
}


void Differentiator::kill_children(Node *node) {
    if (node->left == nullptr || node->right == nullptr) return;

    if (LL != nullptr) destroy_tree_(LL);
    if (LR != nullptr) destroy_tree_(LR);
    if (RL != nullptr) destroy_tree_(RL);
    if (RR != nullptr) destroy_tree_(RR);

    node->left = nullptr;
    node->right = nullptr;
}
