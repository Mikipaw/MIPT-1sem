#ifndef BINARYTREE_BINARYTREE_H
#define BINARYTREE_BINARYTREE_H

#include <cstring>

template <typename T>
class BinaryTree{
    struct Node_
    {
        T data;
        Node_* left;
        Node_* right;

        Node_() = default;
    };


public:

    BinaryTree() { root = nullptr; }

    BinaryTree(T* array, int arr_size);

    ~BinaryTree() { destroy_tree(); }

    bool add(T item);

    Node_* search(T item) { return search_(item, root); }

    void destroy_tree() { destroy_tree_(root); }

    bool contains(T item);

    int get_height() { return get_height_(root); }

    int get_size() { return size; }

    bool is_empty() { return !root; }

    bool erase(T item);



private:
    void destroy_tree_(Node_* node);

    void add_(T item, Node_* node);

    Node_* search_(T item, Node_ *node) {
        if(node != nullptr){
            if(item == node->data) return node;
            if(item < node->data) return search_(item, node->left);
            else return search_(item, node->right);
        }
        else return nullptr;
    }

    int get_height_(const Node_ *node);

    Node_* minValueNode(Node_* node){
        Node_* current = node;
        while(current && current->left != nullptr) current = current->left;
        return current;
    }

    Node_* erase_(T item, Node_* node){
        if (node == nullptr) return node;
        if (item < node->data) node->left = erase_(item, node->left);
        else if(item > node->data) node->right = erase_(item, node->right);
        else {
            if(node->left == nullptr){
                Node_* temp = node->right;
                free(node);
                return temp;
            }
            else if(node->right == nullptr){
                Node_* temp = node->left;
                free(node);
                return temp;
            }
            Node_* temp = minValueNode(node->right);
            node->data = temp->data;
            erase_(node->data, node->right);
        }
        return node;
    }

    size_t size = 1;
    Node_* root;

};


template <typename T>
bool BinaryTree<T>::add(T item) {
    if(this->contains(item)) return false;

    if (root != nullptr) {
        add_(item, root);
        size++;
    }
    else {
        root        = new Node_;
        root->data  = item;
        root->left  = nullptr;
        root->right = nullptr;
    }

    //size++;
    return true;
}

template<typename T>
BinaryTree<T>::BinaryTree(T* array, int arr_size) {
    root = nullptr;
    for (int i = 0; i < arr_size; ++ i) add(array[i]);
}

template<typename T>
bool BinaryTree<T>::contains(T item) {
    Node_* result = search_(item, root);

    return result != nullptr;
}

template<typename T>
bool BinaryTree<T>::erase(T item){
    if (this->contains(item)) {
        root = erase_(item, root);
        size--;

        return true;
    }

    return false;
}

template<typename T>
void BinaryTree<T>::destroy_tree_(Node_* node) {
    if(node != nullptr){
        destroy_tree_(node->left);
        destroy_tree_(node->right);
        delete node;
    }
}

template<typename T>
void BinaryTree<T>::add_(T item, Node_* node){
    if(item < node->data){
        if(node->left != nullptr) add_(item, node->left);
        else{
            node->left = new Node_;
            node->left->data = item;
            node->left->left = nullptr;
            node->left->right = nullptr;
        }
    }
    else if(item >= node->data){
        if(node->right != nullptr) add_(item, node->right);
        else{
            node->right = new Node_;
            node->right->data = item;
            node->right->left = nullptr;
            node->right->right = nullptr;
        }
    }
}

template<typename T>
int BinaryTree<T>::get_height_(const Node_ *node) {
    if (node == nullptr) return 0;

    int lHeight = get_height_(node->left);
    int rHeight = get_height_(node->right);

    if(lHeight > rHeight) return (lHeight + 1);
    else return (rHeight + 1);
}


#endif //BINARYTREE_BINARYTREE_H
