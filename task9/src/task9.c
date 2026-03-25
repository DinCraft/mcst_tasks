#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "array_alg.h"

int *random_array(int size);

int *input_array(int *size);

int main(int argc, char *argv[]) {
  struct timeval tv;
  gettimeofday(&tv,NULL);
  unsigned int time_in_micros = 1000000 * tv.tv_sec + tv.tv_usec;
  srand(time_in_micros);
  int size = (int)1e6;
  //int *array = random_array(size);
  int *array = input_array(&size);
  int i1 = 0, i2 = 0;
  get_subsequence(array, size, &i1, &i2);
  for (int i = i1; i <= i2; i++) {
    printf("%d ", array[i]);
  }
  return 0;
}

int *random_array(int size) {
  int *array = malloc(sizeof(int) * size);
  for (int i = 0; i < size; i++) {
    array[i] = rand() % 100;
  }
  return array;
}

int *input_array(int *size) {
  int counter = 0;
  int n;
  int data_cap = 10;
  int *data = malloc(sizeof(int) * data_cap);
  int *temp;
  while (1) {
    scanf("%d", &n);
    if (counter == data_cap) {
      data_cap *= 2;
      temp = realloc(data, sizeof(int) * data_cap);
      if (temp != NULL) data = temp;
    }
    data[counter] = n;
    char c = getchar();
    counter++;
    if (c == '\n') break;
  }
  *size = counter;
  return data;
}
