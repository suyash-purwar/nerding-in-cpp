#include <stdio.h>

int main() {
  short int valid_small_int = 32767;
  short int invalid_small_int = 32768;

  printf("%hd\n", valid_small_int);

  /**
   * This raises a warning `implicit conversion of int to short`
   */
  printf("%hd\n", invalid_small_int);
}