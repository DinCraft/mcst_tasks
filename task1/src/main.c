#include "stdio.h"
#include "stdlib.h"

struct list {
  int value;
  struct list *next;
};

void list_append_value(struct list *l, int value);

struct list *list_init(int value);

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
    printf("%d ", array[i]);
  }

  return 0;
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
