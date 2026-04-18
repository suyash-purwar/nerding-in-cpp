#include <stdio.h>
#include <stddef.h>

typedef struct Node {
    struct Node* prev;
    struct Node* next;
} node_t;

typedef struct {
    char name[30];
    int age;
    char gender;
    node_t node;
} emp_t;

void print_details(node_t* node) {
    /**
     *  The `offsetof` function tells you the offset of a particular key in a struct from the starting address
     *  of struct in bytes. For example, the size of `emp_t` struct is 48 bytes (structure padding at play.
     *  The position of the node key is at 40th position. This can be dynamically obtained by the `offsetof`
     *  function.
     */
    int offset = offsetof(emp_t, node);

    /**
     * Here, we are trying to obtain the address of the struct given the address of one of it's key. Idea is to
     * subtract the address of the given key by the offset of this key. It would take us to the starting address
     * of the struct.
     */
    emp_t* emp = (emp_t*)((char*)node - offset);

    printf("%s\n", emp -> name);
}

int main(int argc, char* argv[]) {
    node_t node = { NULL, NULL };
    emp_t emp1 = { "Suyash", 23, 1, &node };

    print_details(&emp1.node);

    return 0;
}
