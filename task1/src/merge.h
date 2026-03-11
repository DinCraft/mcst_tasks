#ifndef MERGE_H
#define MERGE_H

struct thread_args {
  int *array;
  int size;
};

void create_threads(int size, int thread_count, int *data, struct thread_args *args);

void merge_sort(int *array, int a, int m, int b);

void *thread_function(void *arg);

int *merge(int size, int thread_count, struct thread_args *args);

#endif // MERGE_H
