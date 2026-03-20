#ifndef PARSER_H
#define PARSER_H

#include <getopt.h>

struct opt_data {
  char mcst[4];
  const char *error;
  struct list *elbrus;
  struct list *non_options;
};

static struct option long_options[] = {
  {"elbrus",  required_argument, 0,  0},
  {0,         0,                 0,  0}
};

struct opt_data *parse(int argc, char *argv[]);

int print(struct opt_data *od);

#endif //PARSER_H
