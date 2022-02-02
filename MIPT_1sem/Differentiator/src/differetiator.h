//
// Created by mikhalinho on 23.11.2021.
//

#ifndef DIFFERENTIATOR_DIFFERETIATOR_H
#define DIFFERENTIATOR_DIFFERETIATOR_H

#include <cmath>
#include "mystr.h"
#include "ErrorList.h"
#include "DSL.h"

inline const char* OUTPUT_FILE_NAME = "Dump_file0.jpg";
inline const char* DOT              = R"(dot Graph.dot -Tjpg -o )";

inline const size_t BUFFER_SIZE = 10000;

inline const char* GOLD     = "gold";
inline const char* LIME     = "lime";
inline const char* AQUA     = "aqua";
inline const char* CRIMSON  = "orangered1";

union Union {
    double  digit       = 0;
    char    variable;
    int     oper;
};

/*!
 * @struct Node
 * @brief classical node of binary tree with bool param
 * @param data - data
 * @param left - pointer to the left childnode
 * @param right - pointer to the right childnode
 * @param question - question (true) or object (false)
 */
struct Node {
    //char* data   = nullptr;
    Node* left   = nullptr;
    Node* right  = nullptr;
    Node* parent = nullptr;

    int type = EMPTY;
    Union data;
};



/*!
 * @function strchar(char* buffer, char sym)
 * @brief Function finds the first symbol 'sym' in string 'buffer' and returns pointer to it (or nullptr if wasn't found)
 * @param buffer - char* (source string)
 * @param sym - char (symbol user wants to find)
 * @return char* - pointer to the first symbol 'sym' in 'buffer'
 */
char* strchar(char* buffer, char sym);


/*!
 * @function bool Is_Equal(Node* root_left, Node* root_right)
 * @brief Compares 2 trees.
 * @param root_left  - first  tree.
 * @param root_right - second tree.
 * @return bool - true or false.
 */
bool Is_Equal(const Node* root_left, const Node* root_right);


/*!
 * @class Differentiator
 * @brief class differentiates the expression from file.
 * @param size          - number of elements in database.
 * @param Elements      - stack which helps to show the objects features.
 * @param root          - pointer to the root of binary tree (first question in the game).
 * @param f_round_str   - string needs to tree traversal.
 * @param text          - string needs to save the text from file in buffer.
 */
class Differentiator {

public:

    //!Classical constructor
    Differentiator() = default;

    //!Constructor is copying tree from root 'new_root'
    explicit Differentiator(Node* new_root) : root(new_root) {}

    //!The constructor creates the tree using the text file.
    explicit Differentiator(const char* input);

    Differentiator(const Differentiator &diff) :
            size(diff.size), root(copy_subtree(diff.Get_root())) {};

    //!Classical destructor
    ~Differentiator() { destroy_tree(); }

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
     * @method Dump()
     * @brief creates the jpg picture of three using 'Graphviz'
     * @warning don't use the function if you don't have Graphviz.
     * @return int - error code
     */
    int
    Dump();


    /*!
     * @method verification()
     * @brief  tests the Differentiator. Recommend to use it before starting game.
     * @return error code (0 if all ok).
     */
    int
    verification() const{ return check(root);};

    [[nodiscard]] const Node*
    Get_root() const { return root;};

    Node*
    differentiate() { return _differentiate(root); };

    /*!
     * @method Node* New_node(...)
     * @brief creating new node.
     * @param node - Node*
     * @param direction - direction LEFT or RIGHT.
     * @param new_type - type of new node, default empty type node.
     * @param left_child - pointer to left child, default nullptr.
     * @param right_child - pointer to right child, default nullptr.
     * @return Node* - pointer to new node. Returns nullptr if direction was written uncorrectly.
     */
    static Node*
    New_node(Node* node, int direction, int new_type = EMPTY,
                          Node* left_child = nullptr, Node* right_child = nullptr);

    /*!
     * @method Node* Create_node(...)
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


    bool Is_const() { return is_const(root);};

    /*!
     * @method Dump_to_TeX();
     * @brief Prints equation and result after differentiation in pdf-file using LaTex.
     * @return error code.
     */
    int Dump_to_TeX();

    /*!
     * @method void optimize();
     * @brief Optimizes equation.
     * @return nothing.
     */
    void optimize (Node* node = nullptr) {
        optimized = true;

        if (node == nullptr) _optimize(root);
        else _optimize(node);
    };

private:

    int _optimize(Node* node);

    void Tree_To_TeX(const Node* node);

    int _dump_to_tex(const Node* node);

    bool is_const(Node* node) const;

    Node* _differentiate(Node* node);

    Node* copy_subtree (const Node* node);

    void destroy_tree_(Node *node);

    void _dumpE (Node* node) const;

    void _dumpV (Node* node) const;

    void f_round_(Node *node);

    int get_height_(const Node *node) const;

    void Read_in_tree(Node* node);

    int check (Node* node) const;

    int oper(Node* node);

    void kill_children(Node* node);

    const char* phrases[10] = {"Несложно заметить, что \n",
                               "Далее делаем небольшой финт ушами \n",
                               "Получаем тривиальное выражение \n",
                               "Такой простой пример сможет решить Матвей Крейнин \n",
                               "Используем метод пристального взгляда \n",
                               "Далее очевидно, что \n",
                               "Воспользуемся способом упрощения Дмитрия Гущина \n",
                               "По следствию 3 из второй великой китайской теоремы об упрощении получим \n",
                               "Такое решают на математическом кружке в пятом классе",
                               "Ещё один финт ушами \n"};

    bool optimized = false;
    int size = 1;
    Node* root;
    char* f_round_str = nullptr;
    char* text = nullptr;
    FILE* LatexFile = fopen("Tex/Dump.tex", "wb");

};

#endif //DIFFERENTIATOR_DIFFERETIATOR_H
