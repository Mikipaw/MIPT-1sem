//
// Created by mikipaw on 29.09.2020.
//
#ifndef STACK_STACK_H
#define STACK_STACK_H


#include <cassert>
#include <cstdio>
#include <stdexcept>
#include <cmath>


#define STACK_CONSTRUCT(stack, capacity, type) Stack<type> stack(5, #stack);
#define NAME(var) #var
//TODO: define this_location (struct)

const long long STRANGE_NUMBER = 0xDEADBEEF;

enum ERRORS{
    SUCCESS,                            //0
    INVALID_POINTER,                    //1
    INVALID_SIZE,                       //2
    CANARY_SCREAM,                      //3
    UNAVAILABLE_ELEMENTS_WAS_CHANGED,   //4
    UNACCEPTABLE_HASH,                  //5
    UNKNOWN_ERROR,                      //6
};

const int INTP       = -661;
const int FLOATP     = 777;
const int DOUBLEP    = 1111;

/*!@function charsum(const char* string)
 * @brief This function finds sum of chars of the string
 * @param string
 * @return an integer - sum of chars
 */
int charsum(const char* string);


/*! \class Stack
 *  \brief This is a stack of memory for storage various elements.
 *  \param data - pointer to block of memory with elements.
 *  \param size - number of elements in Stack.
 *  \param capacity - number of maximum elements can be located in current block of memory.
 *  Some details about the Stack class.
 */
template<typename T>
class Stack{
private:
    const long long canary1 = STRANGE_NUMBER;

public:
    Stack() = default;

    explicit
    Stack(size_t new_capacity):
        capacity (new_capacity),
        size     (0),
        data     (new T[new_capacity]),
        HASH     (charsum(typeid(T).name()) + new_capacity) {
        fill();
    }

    explicit
    Stack(size_t new_capacity, const char* new_name):
            capacity (new_capacity),
            size     (0),
            data     (new T[new_capacity]),
            name     (new_name),
            HASH     (charsum(typeid(T).name()) + new_capacity) {
        fill();
    }


    int
    StackError(int error_number);

    /*!
    *  @method bool push(const T& item).
    *  @brief  Adds element in the end of the stack.
    *  It expands the Stack by one.
    *
    *  @return a bool - true if operation was successful, false - if not
    */
    bool
    push(T item);


    /*!
     *  @method bool pop(T* element).
     *  @brief  Removes last element.
     *  @param element - T*
     *  It shrinks the Stack by one. Deleted item are in element after.
     *
     *  @return a bool - true if success, false if not
     */
    bool
    pop(T* element);

    bool
    pop();

    const T&
    at(int index) const;

    /*!
     *  @method void Destruct().
     *  @brief  Destroys the class.
     *
     *  @return nothing
     */
    void
    Destruct();

    ~Stack() {
        size = -1;
        capacity = -1;
        free(data);
        //*data = 13;
    }


    size_t      Get_Size()      const;
    size_t      Get_Capacity()  const;
    T *         Get_Data()      const;
    const char* Get_Name()      const;

private:

/*!
    *  @method void fill(size_t new_capacity).
    *  @brief  This method fills Stack after constructor call.
    *  @param new_capacity a size_t.
    *
    *  @return nothing
    */
    void fill();

    /*!
    *  @brief  Access to the data contained in the Stack.
    *  @param index The index of the element for which data should be
    *  accessed.
    *  @return  Reference to data.
    */
    T&
    operator[](size_t index);

    /*!
    *  @method void Expand(bool* success).
    *  @brief  This method expands block of memory.
    *  @param success a bool* - true if all is ok, false if expand was unsuccessful.
    *
    *  @return nothing
    */
    void
    Expand(bool* success);

    /*!
    *  @method void Decrease().
    *  @brief  This method decreases block of memory.
    *
    *  @return nothing
    */
    void
    Decrease();

    /*!
    *  @method bool Stack_OK().
    *  @brief  This method checks if stack is OK.
    *
    *  @return bool - true if stack is ok, false if it is not ok.
    */
    bool
    Stack_OK();

    /*!
    *  @method bool Zero(T element).
    *  @brief  This method checks if element is zero.
    *
    *  @return bool - true if element is zero, false it is not zero.
    */
    bool
    Zero(T element);

    /*!@method size_t Hash();
     * @brief counting current hash.
     * @return size_t - current hash.
     */
    size_t Hash(){
       return capacity + charsum(typeid(T).name()) + pow(size*1.0, (size+capacity)%8);
    }

private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
    const char* name = "Nameless stack";
    size_t HASH = 0;

    const long long canary2 = STRANGE_NUMBER;
};

/*!
 * @function str_cmp(const char* str1, const char* str2)
 * @brief Function compares 2 strings
 * @param str1
 * @param str2
 * @return true if strings are equal, false if not
 */
int str_cmp(const char* str1, const char* str2);


template<typename T>
void Stack_info(const Stack<T>& stack);

template<typename T>
void Stack_info(const Stack<T>& stack, FILE* log_file);


template<typename T>
void Print_template_type(const T& var_name);


template<typename T>
void Stack<T>::Destruct(){
    this->Stack_OK();
    free(data);
    size = -1;
    capacity = -1;
}

template<typename T>
bool Stack<T>::pop(T* element){
    if(!this->Stack_OK()) return false;

    if(size == 0) {
        fprintf(stderr, "Logic error at line %d:\n"
                        "It is impossible to delete an element from empty stack\n", __LINE__);
        return false;
    }

    if (HASH != Hash())
        StackError(UNACCEPTABLE_HASH);

    if(size - 1 < capacity/4 && capacity > 16) Decrease();
    size--;

    *element = data[size];

    int sw = charsum(typeid(T).name());
    switch (sw) {
        case 105:   //integer
            data[size] = (T) INTP;
            break;

        case 99:    //char
            data[size] = (T) 0;
            break;

        case 254:   //const char*
            data[size] = (T) (int) "";
            break;

        case 179:   //char*
            data[size] = (T) (int) "";
            break;

        case 102:   //float
            data[size] = (T) FLOATP;
            break;

        case 100:   //double
            data[size] = (T) DOUBLEP;
            break;

        default:
            break;

    }

    this->Stack_OK();
    HASH = Hash();
    return true;
}

template<typename T>
bool Stack<T>::pop(){
    if(!this->Stack_OK()) return false;

    if(size == 0) {
        fprintf(stderr, "Logic error at line %d:\n"
                        "It is impossible to delete an element from empty stack\n", __LINE__);
        return false;
    }

    if (HASH != Hash())
        StackError(UNACCEPTABLE_HASH);

    if(size - 1 < capacity/4 && capacity > 16) Decrease();
    size--;

    int sw = charsum(typeid(T).name());

    switch (sw) {
        case 105:   //integer
            data[size] = INTP;
            break;

        case 99:    //char
            data[size] = 0;
            break;

        case 254:   //const char*
            data[size] = (T) (int) "";
            break;

        case 179:   //char*
            data[size] = (T) (int) "";
            break;

        case 102:   //float
            data[size] = FLOATP;
            break;

        case 100:   //double
            data[size] = DOUBLEP;
            break;

        default:
            break;

    }

    this->Stack_OK();
    HASH = Hash();
    return true;
}

template<typename T>
bool Stack<T>::push(T item){
    if(!this->Stack_OK()) return false;

    bool push_success = true;

    if (HASH != Hash())
        StackError(UNACCEPTABLE_HASH);

    if (size == capacity)
        Expand(&push_success);
    if(!push_success)
        return push_success;

    data[size++] = item;
    this->Stack_OK();
    HASH = Hash();
    return push_success;
}

template<typename T>
int Stack<T>::StackError(int error_number){
    FILE* Log_file = fopen("Logs.txt", "wb");
    switch (error_number) {
        case 1:
            fprintf(Log_file, "Invalid pointer!\n");
            break;

        case 2:
            fprintf(Log_file, "Invalid size!\n");
            break;

        case 3:
            fprintf(Log_file, "Canary was hit!\nCanary1 = %ld\nCanary2 = %ld\n", canary1, canary2);
            break;

        case 4:
            fprintf(Log_file, "Unavailable elements was changed!\n");
            break;

        case 5:
            fprintf(Log_file, "Unacceptable hash!\n");
            break;


        default:
            fprintf(Log_file, "Unknown error!\n");
            Stack_info(*this, Log_file);
            Stack_info(*this);
            Destruct();
            return error_number;
    }
    fprintf(Log_file, "\n");
    Stack_info(*this, Log_file);
    Stack_info(*this);
    fclose(Log_file);
    return 1;
}

template<typename T>
T& Stack<T>::operator[](size_t index){
    if(index < 0 || index >= size) {
        fprintf(stderr, "Out of range error at line %d:\n"
                        "Index %d is out of range!\n", __LINE__, index);
        return nullptr;
    }

    return data[index];
}

template<typename T>
void Stack<T>::Expand(bool* success) {
    (capacity*=2)++;
    data = (T*) realloc(data, capacity*sizeof(T));
    if (data == nullptr) *success = false;

    int sw = charsum(typeid(T).name());
    for (int i = size; i < capacity; ++i) {
        switch (sw) {
            case 105:   //integer
                data[i] = (T) INTP;
                break;

            case 99:    //char
                data[i] = (T) 0;
                break;

            case 254:   //const char*
                data[i] = (T) (int) "";
                break;

            case 179:   //char*
                data[i] = (T) (int) "";
                break;

            case 102:   //float
                data[i] = (T) FLOATP;
                break;

            case 100:   //double
                data[i] = (T) DOUBLEP;
                break;

            default:
                return;
        }
    }
}

template<typename T>
void Stack<T>::Decrease() {
    capacity/=2;
    data = (T*) realloc(data, capacity*sizeof(T));
}

template<typename T>
bool Stack<T>::Stack_OK() {

    if(this == nullptr) {   //NULL POINTER
        StackError(INVALID_POINTER);
        return false;
    }

    if(size > capacity) {   // BAD SIZE
        StackError(INVALID_SIZE);
        return false;
    }

    if(this->data == nullptr) { //NULL POINTER
        StackError(INVALID_POINTER);
        return false;
    }

    if(canary1 != STRANGE_NUMBER || canary2 != STRANGE_NUMBER) { //CANARY WAS HIT
        StackError(CANARY_SCREAM);
        return false;
    }

    int sw = charsum(typeid(data[0]).name());
    for (int i = size; i < capacity; ++i) {
        switch (sw) {
            case 105:   //integer
                if(data[i] == (T) INTP) break;
                StackError(UNAVAILABLE_ELEMENTS_WAS_CHANGED);
                return false;


            case 99:    //char
                if(data[i] != 0) break;
                StackError(UNAVAILABLE_ELEMENTS_WAS_CHANGED);
                return false;


            case 254:   //const char*
                if(str_cmp((const char*) (int) data[i], "")) break;
                StackError(UNAVAILABLE_ELEMENTS_WAS_CHANGED);
                return false;


            case 179:   //char*
                if(str_cmp((const char*) (int) data[i], "")) break;
                StackError(UNAVAILABLE_ELEMENTS_WAS_CHANGED);
                return false;


            case 102:   //float
                if(Zero(data[i] - FLOATP)) break;
                StackError(UNAVAILABLE_ELEMENTS_WAS_CHANGED);
                return false;


            case 100:   //double
                if(Zero(data[i] - DOUBLEP)) break;
                StackError(UNAVAILABLE_ELEMENTS_WAS_CHANGED);
                return false;


            default:
                break;
        }
    }
    return true;
}

template<typename T>
size_t Stack<T>::Get_Size() const { return size; }

template<typename T>
size_t Stack<T>::Get_Capacity() const { return capacity; }

template<typename T>
T* Stack<T>::Get_Data() const { return data; }

template<typename T>
const char* Stack<T>::Get_Name() const { return name; }


template<typename T>
const T& Stack<T>::at(int index) const {
    return *(data + index);
}

template<typename T>
void Stack<T>::fill(){
    int sw = charsum(typeid(T).name());
    for (int i = 0; i < capacity; ++i) {
        switch (sw) {
            case 105:   //integer
                data[i] = (T) INTP;
                break;

            case 99:    //char
                data[i] = (T) 0;
                break;

            case 254:   //const char*
                data[i] = (T) (int) "";
                break;

            case 179:   //char*
                data[i] = (T) (int) "";
                break;

            case 102:   //float
                data[i] = (T) FLOATP;
                break;

            case 100:   //double
                data[i] = (T) DOUBLEP;
                break;

            default:
                return;
        }
    }
}

template<typename T>
void Print_template_type(const T& var_name){
    int a = charsum(typeid(var_name).name());
    switch (a) {
        case 105:   //integer
            printf("%d " , var_name);
            break;

        case 99:    //char
            printf("%c " , var_name);
            break;

        case 254:   //const char*
            printf("%s ", var_name);
            break;

        case 179:   //char*
            printf("%s ", var_name);
            break;

        case 102:   //float
            printf("%f", var_name);
            break;

        case 100:   //double
            printf("%lf", var_name);
            break;

        default:
            printf("unknown type\n");
            fprintf(stderr, "Unknown type!\n");
            return;
    }
}

template<typename T>
void fPrint_template_type(FILE* log_file, const T& var_name){
    int a = charsum(typeid(var_name).name());
    switch (a) {
        case 105:   //integer
            fprintf(log_file, "%d " , var_name);
            break;

        case 99:    //char
            fprintf(log_file, "%c " , var_name);
            break;

        case 254:   //const char*
            fprintf(log_file, "%s ", var_name);
            break;

        case 179:   //char*
            fprintf(log_file, "%s ", var_name);
            break;

        case 102:   //float
            fprintf(log_file, "%f", var_name);
            break;

        case 100:   //double
            fprintf(log_file, "%lf", var_name);
            break;

        default:
            fprintf(log_file, "unknown type\n");
            return;
    }
}


template<typename T>
void Stack_info(const Stack<T>& stack){
    printf("Stack = [%p], \"%s\"\n", &stack, stack.Get_Name());
    printf("{\n");
    printf("\tsize = %d\n",     stack.Get_Size());
    printf("\tcapacity = %d\n", stack.Get_Capacity());
    printf("\tdata [%p]\n",     stack.Get_Data());
    printf("\t{\n");

    for(int i = 0; i < stack.Get_Capacity(); ++i){
        printf("\t\t[%d] = ", i);
        Print_template_type(stack.at(i));
        printf("\n");
    }
    printf("\t}\n");
}

template<typename T>
void Stack_info(const Stack<T>& stack, FILE* log_file){
    fprintf(log_file, "Stack = [%p], \"%s\"\n", &stack, stack.Get_Name());
    fprintf(log_file, "{\n");
    fprintf(log_file, "\tsize = %d\n",     stack.Get_Size());
    fprintf(log_file, "\tcapacity = %d\n", stack.Get_Capacity());
    fprintf(log_file, "\tdata [%p]\n",     stack.Get_Data());
    fprintf(log_file, "\t{\n");

    for(int i = 0; i < stack.Get_Capacity(); ++i){
        fprintf(log_file, "\t\t[%d] = ", i);
        fPrint_template_type(log_file, stack.at(i));
        fprintf(log_file, "\n");
    }
    fprintf(log_file, "\t}\n");
}

template<typename T>
bool Stack<T>::Zero(T element){
    const char* typ = typeid(element).name();
    if(str_cmp(typ, typeid(int).name())) return element == 0;

    if(str_cmp(typ, typeid(const char*).name()) || str_cmp(typ, typeid(char*).name()))
        return str_cmp((const char*) (int) element, "");

    {
        double* a = (double*) &element;
        return (*a < 10e-3 && *a > -10e-3);
    }
    }

inline int charsum(const char* string) {
    char c = 1;
    int result = 0;

    for (int i = 0; c != 0; ++i) {
        c = string[i];
        result += (int) c;
    }
    return result;
}


#endif //STACK_STACK_H
