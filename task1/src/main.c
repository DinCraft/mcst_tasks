#include "stdio.h"
#include "stdlib.h"

struct list {
  int value;
  struct list *next;
};

void list_append_value(struct list *l, int value);

struct list *list_init(int value);

void merge_sort(int *array, int a, int m, int b);

void print_array(int *array, int n);

int main(int argc, char *argv[])
{
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
  int *array = malloc(sizeof(int) * counter);
  current = list;
  for (int i = 0; i < counter; i++) {
    array[i] = current->value;
    current = current->next;
  }
  print_array(array, counter);
  printf("\n");
  merge_sort(array, 0, counter / 2, counter);
  print_array(array, counter);
  printf("\n");

  return 0;
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
