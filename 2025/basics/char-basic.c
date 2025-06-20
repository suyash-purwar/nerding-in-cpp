#include <stdio.h>
#include <string.h>

int main() {
  /**
   * char
   * 
   * A variable of char type is of 1 byte and is always defined by enclosing the value
   * in single-quotation marks.
   */
  
  char char1 = 'A';
  char* char1_ptr = &char1;

  printf("%c\n", char1);
  printf("%p\n", char1_ptr);
  printf("%p\n", char1_ptr + 1); // Moving to the next memory block of 1 byte
  printf("%c\n", *(char1_ptr + 1)); // Printing garbage value
  *(char1_ptr + 1) = 'L';
  printf("%c\n", *(char1_ptr + 1)); // Prints L

  char* char2_ptr = char1_ptr + 1;
  printf("%p\n", char2_ptr);

  /**
   * COOL STUFF HAPPENED ABOVE
   * 
   * 1. char1_ptr and (char1_ptr + 1) is pointing to different memory address
   * 2. char1_ptr stores the address of char1
   * 
   * Cool stuff:
   * 
   * 1. We have assigned a value to a memory address without mapping that memory address
   *    to any variable.
   * 2. At line number 21, we have assigned the address to a pointer variable.
   */

  char* string = "Hello, there";
  printf("%s\n", string);
  printf("%p\n", &string);
  printf("%s\n", *&string);
}
