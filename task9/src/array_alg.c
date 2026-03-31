#include "array_alg.h"

void get_subsequence(int *array, int size, int *_i1, int *_i2) {
  int maxlen = 0;
  int count = 0;
  maxlen_and_count(array, size, &maxlen, &count);
  int sum = array[0];
  int max_sum = 0;
  int length = 1;
  int i1 = 0, i2 = 0;
  int mi1 = 0, mi2 = 0;
  for (int i = 0; i < size - 1; i++) {
    if (array[i + 1] > array[i]) {
      sum += array[i + 1];
      i2++;
      length++;
    }
    else {
      if (length == maxlen) {
        if (max_sum < sum) {
          max_sum = sum;
          mi1 = i1;
          mi2 = i2;
        }
      }
      sum = 0;
      i1 = i;
      i2 = i;
      length = 1;
    }
  }
  if (length == maxlen) {
    if (max_sum < sum) {
      max_sum = sum;
      mi1 = i1;
      mi2 = i2;
    }
  }
  if (mi1 != 0) {
    mi1++;
    mi2++;
  }
  *_i1 = mi1;
  *_i2 = mi2;
}

void maxlen_and_count(int *array, int size, int *maxlen, int *count) {
  int max_length = 0;
  int c = 0;
  int length = 1;
  for (int i = 0; i < size - 1; i++) {
    if (array[i + 1] > array[i]) {
      length++;
    }
    else {
      if (length == max_length) {
        c++;
      }
      if (length > max_length) {
        max_length = length;
        c = 1;
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
