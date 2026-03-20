#include "list.h"
#include <stdlib.h>

void list_add_last(struct list *current, const char *optarg) {
  struct list *new = malloc(sizeof(struct list));
  new->value = optarg;
  new->next = NULL;
  while (current->next != NULL) current = current->next;
  current->next = new;
}
