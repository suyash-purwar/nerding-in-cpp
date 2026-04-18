#include <stdio.h>

int main() {
  FILE* fp = fopen("./files/sample2.txt", "w");

  if (fp == NULL) {
    perror("Failed to open the file");
    return 1;
  }

  /**
   * File is opened in write mode. Before opening it, it truncates the file to 0 bytes. Essentially, all the data
   * is lost. It is important to note that write operations made below are appended in the file.
   * If this file is closed and reopened with `w` mode, all contents of the file will be lost.
   */

  /**
   * fputc -> Writes a single characters
   * fputs -> Writes a string
   * fprintf -> Writes a formatted string
   */
  fputc('A', fp);
  fputc('B', fp);

  fputs("\nBhagat is happy\n", fp);

  char* strings[] = {
    "Why am I an atheist?\n",
    "Because God makes no sense\n"
  };

  for (int i = 0; i < 2; i++) {
    fputs(strings[i], fp);
  }

  const char* name = "Bhagat Singh";
  const int age = 23;

  fprintf(fp, "%s was sentenced to death at the age of %d\n", name, age);

  fclose(fp);

  return 0;
}