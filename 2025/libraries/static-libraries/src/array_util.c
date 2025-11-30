#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_util.h"

void reverse(void* array, const size_t element_size, const size_t array_length) {
  char* start = array;
  char* end = start + (array_length - 1) * element_size;
  char *temp = malloc(element_size);

  while (start < end) {
    memcpy(temp, start, element_size);
    memcpy(start, end, element_size);
    memcpy(end, temp, element_size);

    start += element_size;
    end -= element_size;
  }
}
