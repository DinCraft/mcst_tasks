#include "stdio.h"
#include "stdlib.h"
#include <pthread.h>
#include "merge.h"

int *input(int *size);

int main(int argc, char *argv[])
{
  if (argc != 2) return -1;
  int thread_count = atoi(argv[1]);
  int size = 0;
  int *data = input(&size);
  if (size < thread_count) thread_count = size;
  struct thread_args *args = malloc(sizeof(struct thread_args) * thread_count);
  create_threads(size, thread_count, data, args);
  int *sorted = merge(size, thread_count, args);
  for (int i = 0; i < size; i++) {
    printf("%d ", sorted[i]);
  }
  printf("\n");
  return 0;
}


int *input(int *size) {
  int counter = 0;
  int n;
  int data_cap = 10;
  int *data = malloc(sizeof(int) * data_cap);
  while (1) {
    scanf("%d", &n);
    if (counter == data_cap) {
      data_cap *= 2;
      data = realloc(data, data_cap);
    }
    data[counter] = n;
    char c = getchar();
    counter++;
    if (c == '\n') break;
  }
  *size = counter;
  return data;
}

