#ifndef LIST_H
#define LIST_H

struct list {
  struct list *next;
  const char *value;
};

void list_add_last(struct list *current, const char *optarg);

#endif //LIST_H
