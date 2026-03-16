#include "merge.h"
#include "stdlib.h"
#include <pthread.h>
#include <string.h>

int *merge(int size, int thread_count, struct thread_args *args, pthread_t *threads) {
  int *sorted = malloc(sizeof(int) * size);
  int *thread_idx = malloc(sizeof(int) * thread_count);
  memset(thread_idx, 0, thread_count);
  for (int i = 0; i < size; i++) {
    int t_id = 0;
    int min = 0x7FFFFFFF;
    for (int t = 0; t < thread_count; t++) {
      int v = args[t].array[thread_idx[t]];
      if (thread_idx[t] >= args[t].size) continue;
      if (v < min) {
        min = v;
        t_id = t;
      }
    }
    sorted[i] = args[t_id].array[thread_idx[t_id]];
    thread_idx[t_id]++;
  }
  for (int t = 0; t < thread_count; t++) {
    // освобождение памяти для подмассивов
    free((&args[t])->array);
  }
  free(threads);
  free(thread_idx);
  return sorted;
}

pthread_t *create_threads(int size, int thread_count, int *data, struct thread_args *args) {
  pthread_t *threads = malloc(sizeof(pthread_t) * thread_count);
  float batch_size_f = size / (float)thread_count;
  int n = 0;
  // разбиение массива на части
  for (int i = 0; i < thread_count; i++) {
    struct thread_args *arg = &args[i];
    int a = batch_size_f * (float)i;
    if (a - (int) a > 0.001) {
      a = (int) a + 1;
    }
    int b = batch_size_f * (float)(i + 1);
    if (b - (int) b > 0.001) {
      b = (int) b + 1;
    }
    arg->size = b - a;
    // выделение памяти для подмассивов
    int *array = malloc(sizeof(int) * arg->size);
    for (int i = 0; i < arg->size; i++) {
      array[i] = data[n];
      n++;
    }
    arg->array = array;
    pthread_create(&threads[i], NULL, thread_function, (void*)arg);
  }
  for (int i = 0; i < thread_count; i++) {
    pthread_join(threads[i], NULL);
  }
  return threads;
}

void *thread_function(void *arg) {
  struct thread_args *args = (struct thread_args *) arg;
  int a = 0;
  int b = args->size;
  int m = b / 2;
  merge_sort(args->array, a, m, b);
  return NULL;
}

void merge_sort(int *array, int a, int m, int b) {
  //if (a >= b) return;
  if (b - a == 1) return;
  if (b - a == 2) {
    if (array[a] > array[b - 1]) {
      int t = array[a];
      array[a] = array[b - 1];
      array[b - 1] = t;
    }
    return;
  }
  merge_sort(array, a, a + (m - a) / 2, m);
  merge_sort(array, m, m + (b - m) / 2, b);
  int *temp = malloc(sizeof(int) * (b - a));
  int i1 = a;
  int i2 = m;
  for (int i = 0; i < (b - a); i++) {
    if (i1 < m) {
      if (array[i1] < array[i2] || i2 >= b) {
        temp[i] = array[i1];
        i1++;
        continue;
      }
    }
    if (i2 < b) {
      temp[i] = array[i2];
      i2++;
    }
  }
  for (int i = 0; i < (b - a); i++) {
    array[a + i] = temp[i];
  }
}
