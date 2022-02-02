//
// Created by mikhalinho on 23.11.2021.
//

#include <cassert>
#include <cstdlib>
#include <cstring>

#include "binary_tree.h"
#include "mystr/mystr.h"
#include "Error_codes.h"

void binary_tree::destroy_tree_(Node* node) {
    if(node != nullptr){
        destroy_tree_(node->left);
        destroy_tree_(node->right);
        delete node;
    }
}

int binary_tree::get_height_(const Node *node) const{
    if (node == nullptr) return 0;

    int lHeight = get_height_(node->left);
    int rHeight = get_height_(node->right);

    if(lHeight > rHeight) return (lHeight + 1);
    else return (rHeight + 1);
}


int binary_tree::check (Node* node) const{
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

Node* binary_tree::copy_subtree (const Node* node) {
    if (node == nullptr) return nullptr;

    Node* new_root = new Node;

    new_root->type = node->type;
    new_root->data = node->data;

    new_root->left  = copy_subtree(node->left);
    new_root->right = copy_subtree(node->right);

    return new_root;
}

Node* binary_tree::New_node(Node* node, int direction, int new_type, Node* left_child, Node* right_child) {
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

Node* binary_tree::Create_node(char* new_data, Node* left_child, Node* right_child) {
    Node* node = new Node;
    assert(new_data != nullptr);

    node->type = STAT;
    node->data.statement = new_data;

    if (left_child  != nullptr) node->left  = left_child;
    if (right_child != nullptr) node->right = right_child;

    return node;
}


Node* binary_tree::Create_node(int new_type, double new_data, Node* left_child, Node* right_child) {
    Node* node = new Node;

    node->type = new_type;

    switch (new_type) {
        case DIGITAL:
            DIG = new_data;
            break;
        case VARIABLE:
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

Node* binary_tree::Create_node(int new_type, char* new_data, Node* left_child, Node* right_child) {
    Node* node = new Node;

    node->type = new_type;
    node->data.statement = new_data;

    if (left_child  != nullptr) node->left  = left_child;
    if (right_child != nullptr) node->right = right_child;

    return node;
}


void binary_tree::destroy_tree() {
    destroy_tree_(root);
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
                if (root_left->data.statement != root_right->data.statement) return false;
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


void binary_tree::kill_children(Node *node) {
    if (node->left == nullptr || node->right == nullptr) return;

    if (LL != nullptr) destroy_tree_(LL);
    if (LR != nullptr) destroy_tree_(LR);
    if (RL != nullptr) destroy_tree_(RL);
    if (RR != nullptr) destroy_tree_(RR);

    node->left = nullptr;
    node->right = nullptr;
}


void binary_tree::_print_in_file(Node* node) {
    fprintf(brackets_tree, "{");

    switch (node->type) {
        case DIGITAL:
            fprintf(brackets_tree, "%lg", node->data.digit);
            break;

        case U_OPERATOR:
        case B_OPERATOR:
            fprintf(brackets_tree, "%c", node->data.oper);
            break;

        case STAT:
            if (node->data.statement != nullptr) fprintf(brackets_tree, "%s", node->data.statement);

            break;

        case VARI:
            fprintf(brackets_tree, "'%s'", node->data.statement);
            break;

        default:
            return;
    }


    if (node->right != nullptr) _print_in_file(node->right);
    if (node->left != nullptr) _print_in_file(node->left);

    fprintf(brackets_tree, "}");
}