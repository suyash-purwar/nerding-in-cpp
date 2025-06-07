#include <iostream>

int main() {
    /* & -> address of operatore
     *   -> returns the address of a variable
     *
     * * -> Dereference operator
     *   -> Used to return the value at an address
     */
    
    int a = 10;
    int* b = &a; // b stores the address of variable a
    int** c = &b; // c stores the address of variable b
    
    std::cout << a << std::endl; // value of variable a
    std::cout << &a << std::endl; // address of variable a
    std::cout << b << std::endl; // value of variable b is address of variable a
    std::cout << *b << std::endl; // value at address which variable b stores
    std::cout << &b << std::endl; // address of variable b
    std::cout << c << std::endl;
    std::cout << *c << std::endl;
    std::cout << **c << std::endl;
    
    std::cout << (**c == a) << std::endl;

    return 0;
}