#include "stdio.h"
#include "stdlib.h"
#include <pthread.h>
#include <string.h>
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
  // сортировка проходит в два этапа
  // сначала происходит разбиение массива на число частей, равных кол-ву потоков
  // затем сортировка каждого подмассива в каждом из этих потоков
  pthread_t *threads = create_threads(size, thread_count, data, args);
  // здесь результаты работы потоков объединяются в новый отсортированный массив 
  int *sorted = merge(size, thread_count, args, threads);
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

