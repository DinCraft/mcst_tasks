#include "stdio.h"
#include "stdlib.h"
#include <pthread.h>
#include <string.h>

struct list {
  int value;
  struct list *next;
};

void list_append_value(struct list *l, int value);

struct list *list_init(int value);

void merge_sort(int *array, int a, int m, int b);

void print_array(int *array, int n);

void test(int n);

void *thread_function(void *arg);

struct thread_args {
  int *array;
  int size;
};

int main(int argc, char *argv[])
{
  if (argc != 2) return -1;
  int thread_count = 0;
  thread_count = atoi(argv[1]);
  int n;
  int counter = 0;
  struct list *list = list_init(0);
  struct list *current = list;
  while (1) {
    scanf("%d", &n);
    if (counter == 0) {
      list->value = n;
    }
    else {
      struct list *new = list_init(n);
      current->next = new;
      current = new;
    }
    char c = getchar();
    counter++;
    if (c == '\n') break;
  }
  int **matrix = malloc(sizeof(int*) * thread_count);
  current = list;
  printf("\n");
  pthread_t *threads = malloc(sizeof(pthread_t) * thread_count);
  float batch_size_f = counter / (float)thread_count;
  struct thread_args *args = malloc(sizeof(struct thread_args) * thread_count);
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
    int *array = malloc(sizeof(int) * arg->size);
    for (int i = 0; i < arg->size; i++) {
      array[i] = current->value;
      current = current->next;
    }
    arg->array = array;
    matrix[i] = array;
    pthread_create(&threads[i], NULL, thread_function, (void*)arg);
  }
  for (int i = 0; i < thread_count; i++) {
    pthread_join(threads[i], NULL);
  }

  int *sorted = malloc(sizeof(int) * counter);
  int *thread_idx = malloc(sizeof(int) * thread_count);
  memset(thread_idx, 0, thread_count);
  for (int i = 0; i < counter; i++) {
    int t_id = 0;
    int min = args[0].array[thread_idx[0]];
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
  for (int i = 0; i < counter; i++) {
    printf("%d ", sorted[i]);
  }
  printf("\n");
  return 0;
}

void test(int n) {
  int *array = malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++) {
    array[i] = n - i;
  }
  print_array(array, n);
  merge_sort(array, 0, n / 2, n);
  printf("\n");
  print_array(array, n);
}

void *thread_function(void *arg) {
  struct thread_args *args = (struct thread_args *) arg;
  int a = 0;
  int b = args->size;
  int m = b / 2;
  merge_sort(args->array, a, m, b);
  return NULL;
}

void print_array(int *array, int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", array[i]);
  }
}

void merge_sort(int *array, int a, int m, int b) {
  if (b - a == 1) return;
  if (b - a == 2) {
    if (array[a] > array[b - 1]) {
      int t = array[a];
      array[a] = array[b - 1];
      array[b - 1] = t;
    }
    return;
  }
  merge_sort(array, a, (m - a) / 2, m);
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

struct list *list_init(int value) {
  struct list *list = malloc(sizeof(struct list));
  list->value = value;
  list->next = NULL;
  return list;
}

void list_append_value(struct list *l, int value) {
  struct list *new = malloc(sizeof(struct list));
  new->value = value;
  new->next = NULL;
  l->next = new;
}
