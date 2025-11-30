#include <stdio.h>
#include "array_util.h"
#include "math.h"

int main() {
  const int a = 10;
  const int b = 12;

  const int res = add(a, b);

  float arr1[4] = { 10.2,  35.129, 1.33, 8.8 };
  char arr2[3] = { 'X', '0', '(' };

  reverse(arr1, sizeof(float), 4);
  reverse(arr2, sizeof(char), 3);

  for (int i = 0; i < 4; i++) {
    printf("%f ", arr1[i]);
  }
  printf("\n");

  for (int i = 0; i < 3; i++) {
    printf("%c ", arr2[i]);
  }
  printf("\n");

  printf("Hello, World!\n");

  return 0;
}