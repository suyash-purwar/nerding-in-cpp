#include <stdio.h>

/**
 * char
 * 
 * char is a subtype of int and behaves like integer in many cases.
 * C states: A char, a short int, an int, a long int, and a long long int
 * are all considered integer types
 * 
 * Type promotion/demotion
 * 
 * int d = a + b;
 * Here, char a and b are promoted to int. This is called type promotion
 *
 * int x = 320;
 * char x_demoted = x;
 * 
 * As we know signed char ranges from -127 to 128, what will happen to 320?
 * 
 * 320 = 00000001 01000000
 * 
 * As we know only the last byte will be read. 01000000 = 64.
 * 64 in ASCII is "@".
 * 
 * So, char x_denoted = 64
 */

int main() {
  char a = 30;
  char b = 65;

  char c = a + b; // Becomes 95 which is equal to "_"
  printf("%d\n", c);
  printf("%c\n", c);

  // Char promotion to int
  int d = a + b;
  printf("%d\n", d);

  int x = 320;
  char x_demoted = x;
  printf("%d", 64 == x_demoted);
}
