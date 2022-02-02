//
// Created by mikhalinho on 23.11.2021.
//
#include <cmath>
#include <cstdio>
#include "src/Enums.h"

inline const char* OUTPUT_FILE_NAME = "Dump_file0.jpg";
inline const char* DOT              = R"(dot Graph.dot -Tjpg -o )";

inline const size_t BUFFER_SIZE = 10000;

inline const char* GOLD     = "gold";
inline const char* LIME     = "lime";
inline const char* AQUA     = "aqua";
inline const char* CRIMSON  = "orangered1";
inline const char* LBLUE    = "lightblue";

union Union {
    double  digit       = 0;
    //char    variable;
    int     oper;
    char*   statement;
};

/*!
 * @struct Node_
 * @brief classical node of binary tree with bool param
 * @param data - data
 * @param left - pointer to the left childnode
 * @param right - pointer to the right childnode
 */
struct Node {
    Node* left   = nullptr;
    Node* right  = nullptr;
    Node* parent = nullptr;

    int type = EMPTY;
    Union data;
};


/*!
 * @function bool Is_Equal(Node_* root_left, Node_* root_right)
 * @brief Compares 2 trees.
 * @param root_left  - first  tree.
 * @param root_right - second tree.
 * @return bool - true or false.
 */
bool Is_Equal(const Node* root_left, const Node* root_right);


/*!
 * @class binary_tree
 * @brief class differentiates the expression from file.
 * @param size          - number of elements in database.
 * @param Elements      - stack which helps to show the objects features.
 * @param root          - pointer to the root of binary tree (first question in the game).
 * @param f_round_str   - string needs to tree traversal.
 * @param text          - string needs to save the text from file in buffer.
 */
class binary_tree {

public:

    //!Classical constructor
    binary_tree() = default;

    //!Constructor is copying tree from root 'new_root'
    explicit binary_tree(Node* new_root) : root(new_root) {}

    binary_tree(const binary_tree &diff) :
            size(diff.size), root(copy_subtree(diff.Get_root())) {};

    //!Classical destructor
    ~binary_tree() {
        destroy_tree();
        fclose(brackets_tree);
    }

    /*!
     * @method destroy_tree()
     * @brief This method destroys the binary tree.
     * @return Nothing.
     */
    void
    destroy_tree();

    /*!
     * @method get_height()
     * @brief function recursively finds the height of tree (radius of graph).
     * @return int - height of tree.
     */
    [[nodiscard]] int
    get_height() const { return get_height_(root); }

    [[nodiscard]] int
    get_size() const { return size; }

    bool
    is_empty() { return !root; }


    /*!
     * @method verification()
     * @brief  tests the binary_tree. Recommend to use it before starting game.
     * @return error code (0 if all ok).
     */
    int
    verification() const{ return check(root);};

    [[nodiscard]] const Node*
    Get_root() const { return root;};

    /*!
     * @method Node_* New_node(...)
     * @brief creating new node.
     * @param node - Node_*
     * @param direction - direction LEFT or RIGHT.
     * @param new_type - type of new node, default empty type node.
     * @param left_child - pointer to left child, default nullptr.
     * @param right_child - pointer to right child, default nullptr.
     * @return Node_* - pointer to new node. Returns nullptr if direction was written uncorrectly.
     */
    static Node*
    New_node(Node* node, int direction, int new_type = EMPTY,
                          Node* left_child = nullptr, Node* right_child = nullptr);

    /*!
     * @method Node_* Create_node(...)
     * @brief creating new node.
     * @param new_type - type of new node, default empty.
     * @param new_data - data of new node, default 0.
     * @param left_child - pointer to the left child, default nullptr.
     * @param right_child - pointer to the right child, default nullptr.
     * @return pointer to new node.
     */
    static Node*
    Create_node(int new_type = EMPTY, double new_data = 0,
                Node* left_child = nullptr, Node* right_child = nullptr);


    /*!
     * @method Node_* Create_node(...)
     * @brief creating new Statement node.
     * @param new_data - char*.
     * @param left_child - pointer to the left child, default nullptr.
     * @param right_child - pointer to the right child, default nullptr.
     * @return pointer to new node.
     */
    static Node*
    Create_node(char* new_data = nullptr,
                Node* left_child = nullptr, Node* right_child = nullptr);

    static Node*
    Create_node(int new_type, char* new_data, Node* left_child, Node* right_child);

    void print_in_file() { _print_in_file(root); }

private:

    void _print_in_file(Node* node);

    Node* copy_subtree (const Node* node);

    void destroy_tree_(Node *node);

    int get_height_(const Node *node) const;

    int check (Node* node) const;

    void kill_children(Node* node);

    int size = 1;
    Node* root = new Node;
    char* f_round_str = nullptr;

    FILE* brackets_tree = fopen("Tree.txt", "wb");
};
