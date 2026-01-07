#include <stdio.h>

int main() {
  FILE* fp1 = fopen("./files/sample2.txt", "r");

  while (1) {
    char ch = fgetc(fp1);

    if (ch == EOF)
      break;

    printf("%c", ch);
  }

  printf("\n");
  fclose(fp1);

  FILE* fp2 = fopen("./files/lorem_ipsum_10.txt", "r");
  char* string;

  while (feof(fp2)) {
    fgets(string, 256, fp2);
    printf("%s", string);
  }

  fclose(fp2);
}
