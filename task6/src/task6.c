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
  printf("%7s %-10ld", "Size:", sb.st_size);
  printf("%7s %-10ld", "Blocks:", sb.st_blocks);
  printf("%7s %-10ld", "IO Block:", sb.st_blksize);
  print_file_type(sb.st_mode);
  printf("%7s %d\n", "Uid:", sb.st_uid);
  printf("%7s", "Device:");
  print_device(sb.st_dev);
  printf("%7s %-10ld", "Inode:", sb.st_ino);
  printf("%7s %-10ld", "Links:", sb.st_nlink);
  return 0;
}
