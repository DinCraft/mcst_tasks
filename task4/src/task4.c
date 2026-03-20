#include <getopt.h>
#include "parser.h"


int main(int argc, char *argv[]) {
  struct opt_data *od = parse(argc, argv);
  return print(od);
}
