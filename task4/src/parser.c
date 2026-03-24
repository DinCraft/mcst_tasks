#include "parser.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct opt_data *parse(int argc, char *argv[]) {
  int c;
  opterr = 0;
  struct opt_data *od = malloc(sizeof(struct opt_data));
  od->error = NULL;
  od->non_options = NULL;
  for (int i = 0; i < 4; i++) {
    od->mcst[i] = '-';
  }
  int mcst_ind = 0;

  while (1) {
    int this_option_optind = optind ? optind : 1;
    int option_index = 0;

    c = getopt_long(argc, argv, "mcst", long_options, &option_index);
    if (c == -1) {
       break;
    }
    switch (c) {
    case 0:
      if (option_index == 0) {
        if (od->elbrus == NULL) {
          od->elbrus = malloc(sizeof(struct list));
          od->elbrus->value = optarg;
          od->elbrus->next = NULL;
        }
        else {
          list_add_last(od->elbrus, optarg);
        }
      }
      break;
    case 'm':
    case 'c':
    case 's':
    case 't':
      od->mcst[mcst_ind] = c;
      mcst_ind++;
      break;
    case '?':
      if (od->error == NULL) {
        od->error = argv[optind - 1];
      }
      break;
    default:
      break;
    }
  }

  if (optind < argc) {
    while (optind < argc) {
      if (od->non_options == NULL) {
        od->non_options = malloc(sizeof(struct list));
        od->non_options->value = argv[optind];
        od->non_options->next = NULL;
      }
      else {
        list_add_last(od->non_options, argv[optind]);
      }
      optind++;
    }
  }
  return od;
}

int print(struct opt_data *od) {
  if (od->error != NULL) {
    printf("Incorrect option: ");
    // проверка на длину аргумента
    if (od->error[1] == '-') {
      printf("'%s'\n", &od->error[2]);
    }
    else {
      printf("'%s'\n", &od->error[1]);
    }
    return -1;
  }
  printf("Short options: ");
  for (int i = 0; i < 4; i++) {
    if (od->mcst[i] != '-') {
      printf("'%c' ", od->mcst[i]);
    }
  }
  printf("\n");

  printf("Long options: ");
  struct list *elbrus = od->elbrus;
  while (elbrus != NULL) {
    printf("'elbrus=%s' ", elbrus->value);
    elbrus = elbrus->next;
  }
  printf("\n");

  printf("Non options: ");
  struct list *non_option = od->non_options;
  while (non_option != NULL) {
    printf("'%s' ", non_option->value);
    non_option = non_option->next;
  }
  printf("\n");
  return 0;
}
