#include "stdio.h"
#include "unistd.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  /*
  if (argc != 2) {
    printf("One arg required: fifo filename\n");
    return -1;
  }*/
  if (argc != 3) {
    printf("2 args required: <fifo filename> <rw>\n");
    return -1;
  }
  const char *fifo = argv[1];
  int rw = atoi(argv[2]);
  int fd;
  char str[80];
  //while (1) {
  //}
    
  if (rw == 0) {
    fd = open(fifo, O_RDONLY);
    read(fd, str, 80);
    printf("%s\n", str);
  }
  else {
    fd = open(fifo, O_WRONLY);
    fgets(str, 80, stdin);
    write(fd, str, strlen(str) + 1);
  }
  close(fd);

  return 0;
}
