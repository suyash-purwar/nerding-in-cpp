#include <stdio.h>

int main() {
  FILE* fp1 = fopen("./files/sample1.txt", "r");

  // `w` mode creates the file if it is not present already. If it is present, it will be overwritten.
  FILE* fp2 = fopen("./files/sample2.txt", "w");

  if (fp1 == NULL) {
    perror("Failed to read file");
    return 1;
  }

  /**
   * The perror(char*) function prints a human-readable error message on stderr. It provides context about the failed
   * library or system function. For library functions which set the errno variable, it works in the following way.
   * It internally reads the errno variable and maps the corresponding error message returned by strerror function.
   *
   * `perror` takes an optional string as an input. If the input is not NULL and non-empty string, the output is
   * like this `<input string>: <message from strerror>`. If the input is NULL or empty string, only the message from
   * strerror is printed.
   *
   * If the failing function does not set errno and perror is used, it will either give the last error message
   * from last failed function call as errno does not reset itself to 0 (which represents SUCCESS), or print SUCCESS.
   *
   * Before using perror, check if the function updates errno. `fopen()` does and we are safe to use it.
   */

  if (fp2 == NULL) {
    perror("Failed to create file");
    return 1;
  }

  fclose(fp1);

  if (fclose(fp2)) {
    perror("Failed to close the file");
    return 1;
  }

  /**
   * The fclose() function returns zero on success, or EOF if there is an error in closing the file
   * The fclose() function actually flushes any data still pending in the buffer to the file, closes the file,
   * and releases any memory used for the file. The EOF is a constant defined in the header file stdio.h.
   */

  printf("Read\n");
}