#ifndef MERGE_H
#define MERGE_H

#include <pthread.h>

struct thread_args {
  int *array;
  int size;
};

pthread_t *create_threads(int size, int thread_count, int *data, struct thread_args *args);

void merge_sort(int *array, int a, int m, int b);

void *thread_function(void *arg);

int *merge(int size, int thread_count, struct thread_args *args, pthread_t *threads);

#endif // MERGE_H
