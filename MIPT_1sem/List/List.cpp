//
// Created by mikipaw on 03.11.2020.
//

#include <cmath>
#include "List.h"


int List::Insert(int pos, double value) {
    size_t new_pos = freehead;

    if (List_BAD()) {
        fprintf(stderr, "Current list is broken. Please destroy it and create new object.\n");
        return INVALID_GRAPH;
    }

    if (pos < 0 || pos > capacity) {
        fprintf(stderr, "Index is out of range.\n");
        return OUT_OF_RANGE;
    }

    if (data[pos].prev == -1) {
        fprintf(stderr, "Unavailable element.\n");
        return UNAVAILABLE_ELEMENT;
    }

    if (pos >= head && pos < tail) linearized = false;

    if   (new_pos == capacity + 1) freehead = capacity + 2;
    else freehead = data[new_pos].next;

    if(size == 0) {
        data[new_pos].prev =  0;
        data[new_pos].next = -1;
        data[0].next       = new_pos;
        data[new_pos].item = value;
        size++;

        return new_pos;
    }

    if(size == capacity) Expand();

    data[new_pos].next          = data[pos].next;
    data[data[pos].next].prev   = new_pos;
    data[pos].next              = new_pos;
    data[new_pos].prev          = pos;

    data[new_pos].item = value;

    size++;

    if(data[new_pos].prev ==  0) head = new_pos;
    if(data[new_pos].next == -1) tail = new_pos;

    return new_pos;
}


void List::Expand(bool* success) {
    if (success != nullptr) *success = true;

    if(capacity < LIST_MINIMAL_CAPACITY) {
        capacity = LIST_MINIMAL_CAPACITY;
        data = (List_elem*) realloc(data, (2 + capacity) * sizeof(List_elem));

        if (data == nullptr) {
            *success = false;
            return;
        }

        Fill_new_elems();
        return;
    }
    else {
        capacity *= 2;
        data = (List_elem*) realloc(data, (1 + capacity) * sizeof(List_elem));
        Fill_new_elems();
    }

}


void List::Dump() {
    if (picture_num > '9') {
        fprintf (stderr, "Sorry, the list don't wanna create so many pictures\n");
        return;
    }

    if (List_BAD()) {
        fprintf(stderr, "Current list is broken. Please destroy it and create new object.\n");
        return;
    }

    FILE* Graph = fopen("Graph1.dot", "wb");
    if(Graph == nullptr) fprintf(stderr, "Error opening file!\n");

    const char* DEFAULT_TEXT = "digraph G{\n"
                               "edge [color = \"white\"];\n"
                               "rankdir = \"LR\";\n"
                               "node [shape = record];\n"
                               "node [color = \"#000000\", shape = record];\n"
                               "node0 [style = \"filled\", fillcolor = \"#FF019A\"];\n"
                               "node0 [label = \"<f1> BEGIN\"];\n"
                               "nodeend [style = \"filled\", fillcolor = \"#9F019A\"];\n"
                               "nodeend [label = \"<f1> END\"];\n"
                               "node [color = \"#000000\", shape = record];\n"
                               "nodeinvzero [style = \"filled\", fillcolor = \"#FF019A\"];\n"
                               "nodeinvzero [label = \"<f1> INVALID_ZERO\"];\n\0";
    fwrite(DEFAULT_TEXT, sizeof(char), strlen(DEFAULT_TEXT), Graph);

    fprintf (Graph, "{ rank = same");
    for (int i = 1; i <= capacity; ++i) fprintf (Graph, "node%d ", i);
    fprintf (Graph, "}\n");

    fprintf(Graph, "node0 -> node1:f3;\n");
    for (int i = 1; i <= capacity; ++i) {
        fprintf(Graph, "node%d:f3 -> node%d:f3;\n", i, i + 1);
    }

    fprintf(Graph, "edge [color = \"green\"];\n");
    const char* color = "gold";
    for(int i = 1; i <= capacity; ++i) {
        fprintf(Graph, "node[color = \"blue\", shape = record, style = filled, fillcolor = \"yellow\"];\n");

        if(i % 2 == 0)  color = "gold";
        else            color = "grey";

        fprintf(Graph, "node%d[ penwidth=3, color = \"green\", style=\"filled\", fillcolor = \"%s\"];\n", i, color);

        fprintf (Graph,
                 "node%d [label=\"<f0> prev (%d)|<f1> num (%d)|<f2> next (%d)"
                 "|<f3> data (%.2lf)\"];\n",
                i, data[i].prev, i, data[i].next, data[i].item);

        if (data[i].next != -1) {
            fprintf(Graph, "node%d:f2 -> node%d:f1;\n"
                           "node%d:f0 -> node%d:f1 [color = \"red\"];\n",
            i, data[i].next, data[i].next, i);
        }

        else if(data[i].prev != -1) fprintf(Graph, "node%d:f2 -> nodeend;\n", i);
    }
    fprintf(Graph, "node0       -> node%d:f1;\n"
                   "node%d [style = \"filled\", fillcolor = \"cyan\"];\n"
                   "node%d [label=\"BORDER\"];\n}\n",
                   data[0].next, capacity + 1, capacity + 1);

    fclose(Graph);

    output[PIC_NUM] = picture_num++;

    char*  command1 = (char*) calloc(40, sizeof(char));
    strcpy (command1, DOT);
    strcat (command1, output);

    system (command1);
    system (output);

}

int List::Delete_elem(int pos) {
    if (List_BAD()) {
        fprintf(stderr, "Current list is broken. Please destroy it and create new object.\n");
        return INVALID_GRAPH;
    }

    if (pos > capacity || pos < 1) {
        fprintf(stderr, "Index is out of range.\n");
        return OUT_OF_RANGE;
    }
    if (data[pos].prev == -1) {
        fprintf(stderr, "Unavailable element.\n");
        return UNAVAILABLE_ELEMENT;
    }

    if (pos != head || pos != tail) linearized = false;

    if (pos == head) head = data[pos].next;
    if (pos == tail) tail = data[pos].prev;

    data[data[pos].prev].next = data[pos].next;
    data[data[pos].next].prev = data[pos].prev;

    data[pos].next = freehead;
    freehead = pos;
    data[pos].prev = -1;

    data[pos].item = NAN;

    size--;

    return ALL_OK;
}

void List::Fill_new_elems() {
    for(int i = size + 1; i <= capacity; ++i) {
        data[i].next =  i + 1;
        data[i].prev = -1;
        data[i].item = NAN;
        }
}

int List::List_BAD() const{
    size_t curr_element = 0;
    for(curr_element = head; curr_element != tail; curr_element = data[curr_element].next) {
        if (data[curr_element].next != -1)
            if (data[data[curr_element].next].prev != curr_element) return INVALID_GRAPH;
    }

    for (int i = freehead; data[i].next < capacity + 1; i = data[i].next) {
        if (!std::isnan(data[i].item)) return INVALID_GRAPH;
    }

    return ALL_OK;
}

double List::Get_phys (int index) const {
    if (index < 1 && index > capacity) {
        fprintf(stderr, "Index is out of range.\n");
        return OUT_OF_RANGE;
    }
    if (data[index].prev == -1) {
        fprintf(stderr, "Unavailable element.\n");
        return UNAVAILABLE_ELEMENT;
    }

    return data[index].item;
}

double List::Logical (int index) const {
    if (index < 1 && index > capacity) {
        fprintf(stderr, "Index is out of range.\n");
        return OUT_OF_RANGE;
    }

    size_t i = head;
    while (index > 1) {
        i = data[i].next;
        index--;
    }

    return data[i].item;
}

void List::Linear() {
    double* array = (double*) calloc (capacity + 1, sizeof(double));
    int num = 1;
    for (int i = data[0].next; i != -1; i = data[i].next) {
        array[num] = data[i].item;
        num++;
    }

    free(data);
    data = (List_elem*) calloc (capacity + 1, sizeof(List_elem));

    data[0].next = 1;
    data[0].prev = 0;
    for (int i = 1; i < num; ++i) {
        data[i].prev = i - 1;
        data[i].item = array[i];
        data[i].next = i + 1;
    }
    data[size].next = -1;

    head = 1;
    tail = size;
    linearized = true;
    freehead = size + 1;

    Fill_new_elems();
    free(array);
}