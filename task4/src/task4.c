 #include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
 int c;
 int digit_optind = 0;

  while (1) {
    int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
     {"elbrus",  required_argument, 0,  0 }
    };

    c = getopt_long(argc, argv, "mcst", long_options, &option_index);
    if (c == -1) break;
    switch (c) {
    case 0:
      printf("option %s", long_options[option_index].name);
      if (optarg) {
        printf(" with arg %s", optarg);
      }
      printf("\n");
      break;
    case 'm':
      printf("option m\n");
      break;
    case 'c':
      printf("option c\n");
      break;
    case 's':
      printf("option s\n");
      break;
    case 't':
      printf("option t\n");
      break;
    case 'f':
      printf("option d with value '%s'\n", optarg);
      break;
    case '?':
      break;
    default:
      printf("?? getopt returned character code 0%o ??\n", c);
    }
  }

  if (optind < argc) {
    printf("non-option ARGV-elements: ");
    while (optind < argc) {
      printf("%s ", argv[optind++]);
    }
    printf("\n");
  }

   return 0;
}
