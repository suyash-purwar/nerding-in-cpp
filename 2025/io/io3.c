#include <stdio.h>

int main() {
  FILE* fp1 = fopen("./files/sample2.txt", "r");

  if (fp1 == NULL) {
    perror("Error opening file");
    return 1;
  }

  /**
   * The `feof()` returns non-zero/true value when the EOF has reached. Otherwise, a falsy
   * value is returned. `feof()` returns true only after a read function attempts to read
   * past the actual end-of-file and fails. This leads to one extra garbage character being
   * printed on the screen. It's not the best way to check eof.
   * Use `fgetc()` method directly in loop to check this.
   */

  /*
  while (!feof(fp1)) {
    char ch = fgetc(fp1);

    printf("%c", ch);
  }
  */

  /**
   * The `fgetc()` returns integer version of character when it successfully reads a char.
   * Otherwise, it returns EOF which is equals to -1.
   */
  char ch;
  while((ch = fgetc(fp1)) != EOF) {
    printf("%c", ch);
  }

  printf("\n\n");
  fclose(fp1);


  FILE* fp2 = fopen("./files/sample2.txt", "r");

  char* string;

  /**
   * The `fgets()` function is used to read a line of text from file into character buffer
   * stopping at newline, EOD, or at n-1 characters.
   * Returns the str pointer on success. NULL is returned on reaching EOF or encountering
   * end of file.
   */
  fgets(string, 10, fp2);
  printf("%s\n", string);

  fgets(string, 100, fp2);
  printf("%s\n", string);

  printf("\n");

  while(fgets(string, 10, fp2) != NULL) {
    printf("%s\n", string);
  }

  fclose(fp2);
}
