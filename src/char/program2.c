#include <stdio.h>

/**
 * char
 * 
 * The datatype char is actually an integery type only. It is a subset of integer
 * type and behaves like an integer in many ways.
 * 
 * It ranges from -127 to 128. The first bit represents whether the number is
 * positive or negative.
 * 
 * For example:
 * 
 * 78 --> 01001110
 * -78 --> 2's complement of (01001110)
 *     --> (1's complement of) + 1
 *     --> (Flip all bits) + 1
 *     --> 10110001  + 1
 * -78 --> 10110010
 * 
 * char b = 255;
 * 255 = 11111111
 * 
 * Since char has only 8 bits, it will read MSB (Most Significant bit) as a -ve sign
 * From the POV of char, the value of this octet will be from -127 to 0
 * When the MSB is 1, we take 2's complement and add -ve sign in front
 * 
 * 2's complement of 11111111 is 00000001 which is 1
 * Now, we add - sign.
 * 
 * Hence, "char b = 255" is equivalent to "char b = -1"
 * ASCII value of -1 is not defined
 * ASCII ranges from 0 to 127
 * 
 * 
 * char c = 256
 * 256 = 00000001 00000000
 * But char can hold only 1 byte. Only the last octet is considered (00000000).
 * So, char c = 256 is same char c = 0
 * 
 * Similarly, char d = 258 is same as char d = 2;
 */

int main() {
  char a = 68;

  printf("%d\n", a);
  printf("%c\n", a);

  char b = 255;
  printf("%d\n", b);
  printf("%c\n", b);

  char c = 256;
  printf("%d\n", c);

  char d = 258;
  printf("%d\n", d);
  printf("%c\n", d);
}
