#include "stdio.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("One arg required: <fifo filename>\n");
    return -1;
  }
  const char *fifo = argv[1];
  const int str_size = 128;
  char str[str_size];
  int fd = open(fifo, O_WRONLY | O_NONBLOCK);
  // check if file is NOT opened for reading
  if (fd == -1 && errno == ENXIO) {
    // if NOT opened for reading then open file for it
    fd = open(fifo, O_RDONLY);
    if (fd == -1) {
      perror("Error opening file");
      return -1;
    }
    read(fd, str, str_size);
    printf("%s", str);
    close(fd);

    // now open for writing
    fd = open(fifo, O_WRONLY | O_NONBLOCK);
    if (fd == -1) {
      perror("Error opening file");
      return -1;
    }
    fgets(str, str_size, stdin);
    write(fd, str, str_size);
    close(fd);
  }
  else {
    // already opened
    if (fd == -1) {
      perror("Error opening file");
      return -1;
    }
    fgets(str, str_size, stdin);
    write(fd, str, str_size);
    close(fd);

    fd = open(fifo, O_RDONLY);
    if (fd == -1) {
      perror("Error opening file");
      return -1;
    }
    read(fd, str, str_size);
    printf("%s", str);
    close(fd);
  }
  return 0;
}
