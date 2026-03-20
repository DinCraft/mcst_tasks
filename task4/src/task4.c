#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

struct list {
  struct list *next;
  const char *value;
};

struct opt_data {
  char mcst[4];
  const char *error;
  struct list *elbrus;
  struct list *non_options;
};

int main(int argc, char *argv[]) {
  int c;
  int digit_optind = 0;
  opterr = 0;
  struct opt_data od;
  od.error = NULL;
  od.non_options = NULL;
  for (int i = 0; i < 4; i++) {
    od.mcst[i] = '-';
  }
  int mcst_ind = 0;
  struct list *current2;

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
        struct list *new = malloc(sizeof(struct list));
        new->value = optarg;
        new->next = NULL;
        if (od.elbrus == NULL) {
          od.elbrus = new;
          current2 = new;
        }
        else {
          current2->next = new;
          current2 = current2->next;
        }
      }
      break;
    case 'm':
    case 'c':
    case 's':
    case 't':
      od.mcst[mcst_ind] = c;
      mcst_ind++;
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
    struct list *current;
    while (optind < argc) {
      struct list *new = malloc(sizeof(struct list));
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

  if (od.error != NULL) {
    printf("Incorrect option: ");
    // проверка на длину аргумента
    if (od.error[1] == '-') {
      printf("'%s'\n", &od.error[2]);
    }
    else {
      printf("'%s'\n", &od.error[1]);
    }
    return -1;
  }
  printf("Short options: ");
  for (int i = 0; i < 4; i++) {
    if (od.mcst[i] != '-') {
      printf("'%c' ", od.mcst[i]);
    }
  }
  printf("\n");

  printf("Long options: ");
  struct list *elbrus = od.elbrus;
  while (elbrus != NULL) {
    printf("'elbrus=%s' ", elbrus->value);
    elbrus = elbrus->next;
  }
  printf("\n");

  printf("Non options: ");
  struct list *non_option = od.non_options;
  while (non_option != NULL) {
    printf("'%s' ", non_option->value);
    non_option = non_option->next;
  }
  printf("\n");
  return 0;
}
