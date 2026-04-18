#include <iostream>

void scream(const char* message);

int add(int, int);

int main() {
  std::cout << "Hello, World!" << std::endl;
  scream("aaaaaaa!");
  std::cout << add(1, 3) << std::endl;
  std::cin.get();
}