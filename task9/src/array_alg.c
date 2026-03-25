#include "array_alg.h"
#include <stdio.h>

void get_subsequence(int *array, int size, int *i1, int *i2) {
  int maxlen = 0;
  int count = 0;
  maxlen_and_count(array, size, &maxlen, &count);
  printf("max_length: %d\n", maxlen);
  printf("count: %d\n", count);
}

void maxlen_and_count(int *array, int size, int *maxlen, int *count) {
  int max_length = 0;
  int c= 0;
  int length = 1;
  for (int i = 0; i < size - 1; i++) {
    if (array[i + 1] > array[i]) {
      length++;
    }
    else {
      if (length > max_length) {
        max_length = length;
        c = 1;
      }
      if (length == max_length) {
        c++;
      }
      length = 1;
    }
  }
  if (length == max_length) {
    c++;
  }
  if (length > max_length) {
    max_length = length;
    c = 1;
  }
  *count = c;
  *maxlen = max_length;
}
