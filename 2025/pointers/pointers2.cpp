#include <iostream>

void pointerToAConstant() {
  int a = 10;
  const int* b = &a;

  // Not permitted as it tries to change the value of
  // assigned at an address that is associated with a
  // constant type of variable
  // *b = 20;
  
  std::cout << b << std::endl;
  std::cout << *b << std::endl;

  // We can directly change the value of a nonetheless
  a = 99;
  std::cout << *b << std::endl;

  // We can change the value of variable b --- change
  // the address stored by another address
  int c = 200;
  b = &c;

  std::cout << b << std::endl;
  std::cout << *b << std::endl; 
}

void constantPointer() {
  int a = 94, b = 40;
  int* const c = &a;

  // Not permitted as the entire variable is constant here.
  // But the value at address can be changed.
  // c = &b
  *c = 78;

  // Try the following. Uncomment it.
  // const int e = 31, g = 72;
  // int* const f = &e;

  // Not permitted. `const int e` signifies the variable e is
  // of constant type and it's value cannot be altered.
  // Whereas `int* const f` signifies that:
  // 1) variable f is of constant type, ie. it's value (address of e) cannot change
  // 2) But it doesn't block the updation of value of variable e
  // Had this been possible, it would allow the updation of constant variable a

  // To make it work, we can use `Constant Pointer to a Constant`
  // Eg: const int* const f = &e;
}

void constantPointerToAConstant() {
  int a = 18, b = 230;
  const int* const c = &a;

  // Here changing both the value of variable c and the value at
  // the address stored is not permitted.
  // c = &b;
  // *c = 30;

  std::cout << *c << std::endl;

  // But you can indirectly change the value which variable c points to
  a = 30;

  std::cout << *c << std::endl;
}

int main() {
  pointerToAConstant();
  constantPointer();
  constantPointerToAConstant();
}