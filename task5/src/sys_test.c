#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define BLOCK_SIZE 32

int main(int argc, char *argv[]) {
  char *src_file = "src_file.txt";
  char *dest_file = "copied_file.txt";
  
  int dest_fd, src_fd, read_byte, write_byte;
  char read_buf[BLOCK_SIZE];

  dest_fd = open(dest_file, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IROTH);

  if (dest_fd < 0) {
    perror("Error opening the destination file");
    exit(1);
  }
  else {
    fprintf(stderr, "Successfully opened the destination file..");
  }

  src_fd = open(src_file, O_RDONLY);

  if (src_fd < 0) {
    perror("\nError opening the source file\n");
    exit(1);
  }
  else {
    fprintf(stderr, "\nSuccessfully opened the source file..\n");
  }

  while (1) {
    read_byte = read(src_fd, read_buf, BLOCK_SIZE);
    if (read_byte == 0) {
      fprintf(stdout, "Reached the EOF for src file\n");
      break;
    }
    printf("read %d bytes\n", read_byte);
    printf("Buffer: \n");
    for (int i = 0; i < BLOCK_SIZE; i++) {
      printf("%c", read_buf[i]);
    }
    printf("\n");
    /*if (BLOCK_SIZE - read_byte != 0) {
      write_byte = write(dest_fd, read_buf, BLOCK_SIZE - read_byte);
    }
    else {
      write_byte = write(dest_fd, read_buf, BLOCK_SIZE);
    }*/
    if (write_byte < 0) {
      perror("Error writing file");
      exit(1);
    }
  }

  close(src_fd);
  close(dest_fd);

  return 0;
}
