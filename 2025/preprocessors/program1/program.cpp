#include <iostream>

#define INTEGER int
#define INTEGER_POINTER int*

#if 1
  #define NAME "suyash"
#endif

#if 0
  char* pwd = "suyash"
#endif

INTEGER main()
#include "start-brace.h"
  INTEGER a = 1;
  INTEGER_POINTER a_pointer = &a;

  std::cout << a_pointer << std::endl;
  std::cout << NAME << std::endl;
#include "end-brace.h"
