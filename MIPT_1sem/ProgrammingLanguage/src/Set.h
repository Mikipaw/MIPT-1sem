#ifndef BINARYTREE_SET_H
#define BINARYTREE_SET_H

#include <cstdio>
#include <stdexcept>

#include "BinaryTree.h"
#include "mystr/mystr.h"
#include "Stack.h"

bool isprcnt(char* new_data);

struct variable {
    explicit variable(const char* new_name, double new_data, int new_number) :
        data   (new_data),
        name   (new_name),
        number (new_number)
    {}

    explicit variable(const char* new_name) :
            name   (new_name)
    {}

    explicit variable(const char* new_name, int new_number) :
            name (new_name),
            number (new_number) {}

    explicit variable() = default;

    const char* name = nullptr;
    double data = 0;
    int number = 0;

    ~variable() = default;
};

struct function {
    explicit function(const char* new_name, int new_number, int args = 0) :
            name (new_name),
            number_of_args(args),
            number (new_number)
            {}

    explicit function(const char* new_name) :
            name (new_name)
    {}

    const char* name = nullptr;
    int number_of_args = 0;
    int number         = 0;
    //double data;
    function() = default;

    ~function() = default;
};


/*!
 * @class Set
 * @brief Based on red-black tree (binary tree)
 * @tparam T
 * @param BinaryTree
 * This is an associative container that contains a sorted set of unique objects of type T.
 * Sorting is done using the key comparison function Compare.
 */
template <typename T>
class Set {
public:
    //default constructor
    Set<T>() { this->list = new BinaryTree<T>; }

    //This constructor creates tree with elements in new_list
    Set<T>(T* new_list, int new_size) { this->list = new BinaryTree<T>(new_list, new_size); }

    //Returns the element with index index
    T get(int index) const;

    T change(T elem);

    T search(T object) { return list->search(object)->data; }

    T search(T object) const { return list->search(object)->data; }


    /*!
     * @fn bool delete_elem(T item)
     * @brief this function deletes item
     * @param item
     * @return true if item was deleted successfully, false if item wasn't found in Set
     */
    bool delete_elem(T item) { return this->list->erase(item); }

    /*!
     * @fn Set<T> concat(const Set<T>& new_set)
     * @brief This function creates new set as a sum of current set and new_set
     * @param new_set
     * @return Set<T> - new set
     */
    Set<T> concat(const Set<T>& new_set);

    /*!
     * @fn Set<T> intersection(const Set<T>& new_set)
     * @brief This function creates new set that contains the elements from intersection of 2 sets.
     * @param new_set
     * @return Set<T> - intersection of 2 sets
     */
    Set<T> intersection(const Set<T>& new_set);

    //Check for availability the elem
    bool HasElement(const T& elem) const { return list->contains(elem); }

    //Adding new item in set
    void Add(const T& item);

    friend bool operator==(const Set<T>& set1, const Set<T>& set2)
        { return set1.list->f_round() == set2.list->f_round(); }

    T& changik(const Set<T>& new_set);

    //Logical subtraction between set1 and set2
    friend Set<T> operator-(const Set<T>& set1, const Set<T>& set2) {
        Set<T> result;
        T item;
        for (int i = 0; i < set1.Get_Length(); ++i){
            item = set1.get(i);
            if (!set2.HasElement(item)) result.Add(item);
        }

        return result;
     }

     //Returns number of elements in Set
    [[nodiscard]] size_t Get_Length ()const { return list->get_size(); }

    /*!
     * @fn bool subset(const Set<T>& set)
     * @brief checks if set is subset of the current Set
     * @param set
     * @return true or false
     */
    bool subset(const Set<T>& set);


    ~Set<T>() = default;

private:
    BinaryTree<T>* list;
};

template<typename T>
T Set<T>::get(int index) const {
    if (index < 0 || index > this->Get_Length()) throw std::out_of_range("Index out of range!");
    return this->list->elements()[index];
}

template<typename T>
Set<T> Set<T>::concat(const Set<T>& new_set){
    Set<T> result = new_set;
    for (int i = 0; i < this->Get_Length(); ++i) result.Add(this->get(i));

    return result;
}

template<typename T>
Set<T> Set<T>::intersection(const Set<T>& new_set) {
    Set<T> result;
    T elem;

    if (this->Get_Length() < new_set.Get_Length()){
        for (int i = 0; i < this->Get_Length(); ++i){
            elem = this->get(i);
            if (new_set.HasElement(elem)) result.Add(elem);
        }
    }
    else{
        for (int i = 0; i < new_set.Get_Length(); ++i){
            elem = new_set.get(i);
            if (this->HasElement(elem)) result.Add(elem);
        }
    }

    return result;
}
template <typename T>
T& Set<T>::changik(const Set<T>& new_set) {
    Set<T> result;
    T elem;

}

template<typename T>
void Set<T>::Add(const T& item){
    if (this->HasElement(item)) return;
    list->add(item);
}

template<typename T>
bool Set<T>::subset(const Set<T>& set) {
    if (set.Get_Length() > this->Get_Length()) throw std::logic_error("Subset can't be bigger then set");
    for (int i = 0; i < set.Get_Length(); ++i) if (!this->HasElement(set.get(i))) return false;
    return true;
}


template<typename T>
T Set<T>::change(T elem) {
    return search(elem);
}

inline bool operator==(const variable& ss1, const variable& ss2) {
    if (!str_cmp(ss1.name, ss2.name)) return true;
    else return false;
}

inline bool operator>(const variable& ss1, const variable& ss2) {
    return str_cmp(ss1.name, ss2.name) > 0;
}

inline bool operator>=(const variable& ss1, const variable& ss2) {
    return str_cmp(ss1.name, ss2.name) >= 0;
}

inline bool operator<(const function& ss1, const function& ss2) {
    return str_cmp(ss1.name, ss2.name) < 0;
}

inline bool operator<=(const function& ss1, const function& ss2) {
    return str_cmp(ss1.name, ss2.name) <= 0;
}

inline bool operator==(const function& ss1, const function& ss2) {
    if (!str_cmp(ss1.name, ss2.name)) return true;
    else return false;
}

inline bool operator>(const function& ss1, const function& ss2) {
    return str_cmp(ss1.name, ss2.name) > 0;
}

inline bool operator>=(const function& ss1, const function& ss2) {
    return str_cmp(ss1.name, ss2.name) >= 0;
}

inline bool operator<(const variable& ss1, const variable& ss2) {
    return str_cmp(ss1.name, ss2.name) < 0;
}

inline bool operator<=(const variable& ss1, const variable& ss2) {
    return str_cmp(ss1.name, ss2.name) <= 0;
}

inline bool isprcnt(char* new_data) {
    if (strchr(new_data, '%') != nullptr)  {
        size_t size = strlen(new_data);

        for (int i = 0; i < size; ++i)
            if (new_data[i] != '%' && !is_digit(new_data[i]))
                return false;

        return true;
    }
    else return false;
}

#endif //BINARYTREE_SET_H
