#include <stdio.h>
#include <getopt.h>
#include <signal.h>
#include "matrix.h"

static struct option long_options[] = {
  {"signal",    no_argument, 0,  0},
  {"sigaction", no_argument, 0,  0},
  {0,           0,           0,  0}
};

void signal_handler(int sigid);

void sigaction_handler(int sigid);

extern int result_row, result_column, iter_index;

void print_data();

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("One argument required: --signal or --sigaction\n");
    return -1;
  }
  int option_index = 0;
  int c = getopt_long(argc, argv, "", long_options, &option_index);
  if (c == 0) {
    if (option_index == 0) {
      signal(SIGINT, signal_handler);
    }
    else if (option_index == 1) {
      struct sigaction sa;
      sa.sa_handler = sigaction_handler;
      sigaction(SIGINT, &sa, NULL);
    }
  }
  struct matrix m1, m2;
  fill_matrix(&m1, 1);
  fill_matrix(&m2, 101);
  struct matrix result;
  multiply_matrix(&m1, &m2, &result);
  return 0;
}

void print_data() {
  printf("\n");
  printf("%d %d\n", result_row, iter_index);
  printf("%d %d\n", iter_index, result_column);
  printf("%d %d\n", result_row, result_column);
}

void signal_handler(int sigid) {
  print_data();
  signal(SIGINT, NULL);
}

void sigaction_handler(int sigid) {
  print_data();
  struct sigaction sa;
  sa.sa_handler = SIG_DFL;
  sigaction(SIGINT, &sa, NULL);
}
