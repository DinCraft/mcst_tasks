#include "stdio.h"
#include "getopt.h"
#include <bits/getopt_ext.h>

static struct option long_options[] = {
  {"signal",    no_argument, 0,  0},
  {"sigaction", no_argument, 0,  0},
  {0,           0,           0,  0}
};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("One argument required: --signal or --sigaction\n");
    return -1;
  }
  int option_index = 0;
  int c = getopt_long(argc, argv, "", long_options, &option_index);
  if (c == 0) {
    if (option_index == 0) {
      printf("signal\n");
    }
    else if (option_index == 1) {
      printf("sigaction\n");
    }
  }
  else {
    printf("idk\n");
  }
  return 0;
}
