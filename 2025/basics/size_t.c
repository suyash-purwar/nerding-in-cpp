#include <stdio.h>

/** 
  * sizeof, size_t, and %zu
  * 
  * 1. This function returns the size of entity in bytes. It can print size of arrays, objects, variable, buffers, etc
  * 2. Return type of sizeof function is size_t
  * 3. C Standard Library ensures that size_t is big enough to hold the size of the biggest object that the
  *    system can handle / maximum size of any object that can be allocated in memory.
  * 4. Now, the maximum permissible size is dependent on the compiler. If compiler is 32 bit, then size_t is 
  *     same as unsigned int but if the compiler is 64 bit, then size_t is unsigned long long.
  * 5. The format specifier for a compiler-dependent data type will also be dynamic in nature. It is %zu for unsigned
  *    integer and %zd for signed integer
  */

int main()
{
  printf("Hello, World!\n");
  printf("Back to C. After %d years probably\n", 3);

  printf("%zu\n", sizeof(int));

  printf("%zu\n", sizeof(long));

  printf("%zu\n", sizeof(long long));

  printf("%zu\n", sizeof(size_t));

  /*
  | Data Type   | 32-bit system | 64-bit system (Linux/GCC/Clang) | Windows 64-bit (MSVC) |
  | ----------- | ------------- | ------------------------------- | --------------------- |
  | `int`       | 4 bytes       | 4 bytes                         | 4 bytes               |
  | `long`      | 4 bytes       | 8 bytes                         | 4 bytes               |
  | `long long` | 8 bytes       | 8 bytes                         | 8 bytes               |
  */

  // True for 64-bit systems
  printf("%d", sizeof(size_t) == sizeof(long long) == sizeof(long));

  return 0;
}