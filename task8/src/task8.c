#include <stdio.h>
#include <getopt.h>
#include <signal.h>

static struct option long_options[] = {
  {"signal",    no_argument, 0,  0},
  {"sigaction", no_argument, 0,  0},
  {0,           0,           0,  0}
};

void signal_handler(int sigid);

void sigaction_handler(int sigid);

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
      signal(SIGINT, signal_handler);
    }
    else if (option_index == 1) {
      printf("sigaction\n");
      struct sigaction sa;
      sa.sa_handler = sigaction_handler;
      sigaction(SIGINT, &sa, NULL);
    }
  }
  else {
    printf("idk\n");
  }
  while (1) {}
  return 0;
}

void signal_handler(int sigid) {
  printf("sigint\n");
  signal(SIGINT, NULL);
}

void sigaction_handler(int sigid) {
  printf("sigint\n ");
  struct sigaction sa;
  sa.sa_handler = SIG_DFL;
  sigaction(SIGINT, &sa, NULL);
}
