//
// Created by pawlo on 01.10.2020.
//
/*
#include <cstdlib>
#include <stdexcept>
#include "Stack.h"*/

/*
template<typename T>
void Stack<T>::Destruct(){
    assert(this);
    free(data);
    data = 13;
    size = -1;
    capacity = -1;
}

template<typename T>
T Stack<T>::pop(){
    assert(this);
    if(size == 0) throw std::logic_error("It is impossible to delete element from empty stack\n");
    if(size - 1 < capacity/4) Decrease();
    return data[size--];
}

template<typename T>
bool Stack<T>::push(T item){
    assert(this);
    bool flag = true;
    if (size == capacity) Expand(&flag);
    data[size] = item;
    return flag;
}

template<typename T>
int Stack<T>::StackError(){
    return 0;
}

template<typename T>
T& Stack<T>::operator[](size_t index){
    if(index < 0 || index >= size) throw std::out_of_range("Index out of range! __LINE__\n");
    return data[index];
}

template<typename T>
void Stack<T>::Expand(bool* flag) {
    (capacity*=2)++;
    data = (T*) realloc(nullptr, capacity*sizeof(T));
    if(data == nullptr) *flag = false;
}

template<typename T>
void Stack<T>::Decrease() {
    capacity/=2;
    data = (T*) realloc(data, capacity*sizeof(T));
}*/

int charsum(const char* string) {
    char c = 1;
    int result = 0;

    for (int i = 0; c != 0; ++i) {
        c = string[i];
        result += (int) c;
    }
    return result;
}

int str_cmp(const char* str1, const char* str2){
    int i = 0;
    while (true) {
        if(str1[i] == '\0' && str2[i] == '\0') return true;
        if(str1[i] == str2[i]){
            ++i;
            continue;
        }
        return false;
    }
}
