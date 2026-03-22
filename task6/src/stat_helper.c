#include "stat_helper.h"
#include <stdio.h>
#include <sys/stat.h>

void print_file_type(unsigned int st_mode)
{
  switch (st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break;
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown?\n");                break;
  }
}

void print_device(unsigned int st_dev)
{
  // через калькулятор выяснил формат хранения этих параметров
  unsigned int v1 = (st_dev & 0x0F00) >> 8;
  unsigned int v2 = st_dev & 0x00FF;
  printf(" %d, %-7d", v1, v2);
}
