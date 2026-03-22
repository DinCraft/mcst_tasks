#include "stdio.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("One arg required: <fifo filename>\n");
    return -1;
  }
  const char *fifo = argv[1];
  int fd = open(fifo, O_WRONLY | O_NONBLOCK);
  char str[80];
  if (fd == -1 && (errno == ENXIO || errno == EAGAIN)) {
    fgets(str, 80, stdin);
    fd = open(fifo, O_WRONLY);
    if (fd == -1) {
      perror("Error opening file");
      return -1;
    }
    write(fd, str, 80);
    close(fd);

    fd = open(fifo, O_RDONLY);
    if (fd == -1) {
      perror("Error opening file");
      return -1;
    }
    read(fd, str, 80);
    printf("%s\n", str);
    close(fd);
  }
  else {
    if (fd != -1) {
      close(fd);
    }
    fd = open(fifo, O_RDONLY);
    if (fd == -1) {
      perror("Error opening file");
      return -1;
    }
    read(fd, str, 80);
    printf("%s\n", str);
    close(fd);

    fgets(str, 80, stdin);
    fd = open(fifo, O_WRONLY);
    if (fd == -1) {
      perror("Error opening file");
      return -1;
    }
    write(fd, str, 80);
    close(fd);
  }

  return 0;
}
