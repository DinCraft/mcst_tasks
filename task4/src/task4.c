#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

struct non_opt {
  struct non_opt *next;
  const char *value;
};

struct opt_data {
  char m, c, s, t;
  const char *elbrus;
  const char *error;
  struct non_opt *non_options;
};

int main(int argc, char *argv[]) {
  int c;
  int digit_optind = 0;
  opterr = 0;
  struct opt_data od;
  od.error = NULL;
  od.non_options = NULL;
  od.m = 0;
  od.c = 0;
  od.s = 0;
  od.t = 0;

  while (1) {
    int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
      {"elbrus",  required_argument, 0,  0},
      {0,         0,                 0,  0}
    };

    c = getopt_long(argc, argv, "mcst", long_options, &option_index);
    if (c == -1) {
       break;
    }
    switch (c) {
    case 0:
      if (option_index == 0) {
        od.elbrus = optarg;
      }
      break;
    case 'm':
      od.m = 1;
      break;
    case 'c':
      od.c = 1;
      break;
    case 's':
      od.s = 1;
      break;
    case 't':
      od.t = 1;
      break;
    case '?':
      /*if (optopt == 1) {
        printf("elbrus found!\n");
      }
      else {
        printf("unknown option: %d\n", optopt);
      }*/
      od.error = argv[optind - 1];
      break;
    default:
      printf("?? getopt returned character code 0%o ??\n", c);
    }
  }

  if (optind < argc) {
    struct non_opt *current;
    while (optind < argc) {
      struct non_opt *new = malloc(sizeof(struct non_opt));
      new->value = argv[optind];
      new->next = NULL;
      if (od.non_options == NULL) {
        od.non_options = new;
        current = od.non_options;
      }
      else {
        current->next = new;
        current = current->next;
      }
      optind++;
    }
  }

  struct non_opt *non_option = od.non_options;
  while (non_option != NULL) {
    printf("%s\n", non_option->value);
    non_option = non_option->next;
  }

  return 0;
}
