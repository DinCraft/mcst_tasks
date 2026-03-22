#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include "libgen.h"
#include "stat_helper.h"

int main(int argc, char *argv[])
{
  struct stat sb;
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <path>\n", argv[0]);
    return -1;
  }

  if (stat(argv[1], &sb) == -1) {
    perror("stat");
    return -1;
  }
  printf("%7s %s\n", "File:", argv[1]);
  printf("%7s %-10ld Blocks: %-10ld IO Block: %-10ld", "Size:", sb.st_size, sb.st_blocks, sb.st_blksize);
  print_file_type(&sb);
  printf("Uid: %d\n", sb.st_uid);
  
  return 0;
}
