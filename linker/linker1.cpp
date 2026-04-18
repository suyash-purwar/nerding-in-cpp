#include <iostream>
#include <string>
#include "linker1-internal.cpp"

extern std::string name;
extern std::string sayMyName(std::string);

// This would give linker error as the variable int is defined as const
// extern int age;

void printFromDifferentFile() {
  std::cout << name << std::endl;
}

int main() {
  printFromDifferentFile();
  std::cout << sayMyName("suyash") << std::endl;

  std::cout << someText << std::endl;

  std::cout << someTextPtr << std::endl;
}
