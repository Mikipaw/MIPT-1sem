//
// Created by mikipaw on 02.11.2020.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <cstdio>
#include <cstdlib>

#include "ErrorList.h"
#include <cstring>

#define to_str(x) #x

inline const char* DOT = R"(dot Graph1.dot -Tjpg -o )";
const int PIC_NUM = 9;

/*!
 * @struct List_elem
 * @brief Just an element of list.
 * @param next an integer - 'pointer' to next element in list.
 * @param prev an integer - 'pointer' to previous element in list.
 * @param item a double - element in list.
 */
struct List_elem {
    int     next = -1;
    int     prev = -1;
    double  item =  0;
    //int     logc =  0;
};

/*!
 * @class List
 * @brief This class contains some elements.
 * @param data a List_elem* - array with elements.
 * @param head a List_elem* - pointer to first elem.
 * @param tail a List_elem* - pointer to last element.
 * @param size a size_t - number of elements in list.
 * @param capacity a size_t - capacity.
 */

const size_t LIST_MINIMAL_CAPACITY = 16;

class List{

private:
    List_elem* data;

    size_t  head        = 0;
    size_t  tail        = 0;
    size_t  size        = 0;
    size_t  capacity    = 0;
    size_t  freehead    = 1;

    bool linearized  = true;

    char picture_num = '0';
    char output[16]  = "dump_file0.jpg";

public:

    /*!
     * List(size_t new_capacity);
     * @brief Classic constructor.
     * @param new_capacity
     */
    explicit
    List(size_t new_capacity):
            capacity    (new_capacity),
            data        ((List_elem*) calloc(new_capacity + 1, sizeof(List_elem)))
            {
                Fill_new_elems();
                data[0].prev = 0;
            }

    /*!
     * @method Insert(int pos, const double& value);
     * @brief The method inserts element in position pos.
     * @param pos an integer - position.
     * @param value a double - element to insert in list.
     * @return an integer - position of added element.
     */
    int Insert(int pos, double value);

    /*!
     * @method Delete_elem(int pos);
     * @brief The method deletes element in position pos.
     * @param pos an integer - position of deleting element.
     * @return an integer - position
     */
    int Delete_elem(int pos);

    /*!
     * @method Dump() const;
     * @brief The method prints information about the list.
     * @return nothing?
     */
    void Dump();

    /*!
     * @method Linear();
     * @brief This function is linearising list
     * @return nothing
     */
    void Linear();

    [[nodiscard]] double Get_phys (int index) const;
    [[nodiscard]] double Logical  (int index) const;

    List& operator=(const List& list)   = delete;
    List           (const List&)        = delete;

    ~List(){
        delete[] data;
    }

    [[nodiscard]] size_t    Get_tail()      const { return tail; }
    [[nodiscard]] size_t    Get_head()      const { return head; }
    [[nodiscard]] size_t    Get_size()      const { return size; }
    [[nodiscard]] bool      Is_Linearized() const { return linearized; }

private:
    /*!
     * @method Expand(bool* succes = nullptr);
     * @brief The method expands the list.
     * @param success - success of the operation.
     * @return nothing.
     */
    void Expand(bool* success = nullptr);

    /*!
     * @method Fill_new_elems();
     * @brief The method fills the list by empty elements.
     * @return nothing.
     */
    void Fill_new_elems();


    /*!
     * @method List_BAD();
     * @brief Classic verifier for the list.
     * @return ERROR CODE.
     */
    int List_BAD() const;

};






#endif //LIST_LIST_H
