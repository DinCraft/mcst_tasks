#include "stdio.h"
#include "syscall.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char **input(FILE *input_file, int *lines_amount);

int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("One argument required: <path_to_file>\n");
    return -1;
  }
  pid_t p;
  p = fork();
  if(p<0) {
    perror("fork fail");
    exit(1);
  }
  else if ( p == 0) {
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
      printf("Error: file '%s' not found!\n", argv[1]);
      return -1;
    } 
    int lines_amount = 0;
    char **lines = input(input_file, &lines_amount);
    fclose(input_file);

    FILE *output_file = fopen("child_copy", "w");
    for (int i = 0; i < lines_amount; i++) {
      fputs(lines[i], output_file);
    }
    fclose(output_file);
  }
  else {
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
      printf("Error: file '%s' not found!\n", argv[1]);
      return -1;
    } 
    int lines_amount = 0;
    char **lines = input(input_file, &lines_amount);
    fclose(input_file);

    FILE *output_file = fopen("parent_copy", "w");
    for (int i = 0; i < lines_amount; i++) {
      fputs(lines[i], output_file);
    }
    fclose(output_file);
  }

  return 0;
}

char **input(FILE *input_file, int *lines_amount) {
  char buffer[256];
  int array_size = 4;
  char **lines = malloc(sizeof(char*) * array_size);
  if (lines == NULL) return NULL;
  int idx = 0;
  while (fgets(buffer, 256, input_file) != NULL) {
    if (idx == array_size) {
      array_size *= 2;
      char **temp = realloc(lines, sizeof(char*) * array_size);
      if (temp != NULL) lines = temp;
    }
    lines[idx] = malloc(sizeof(char) * 256);
    strcpy(lines[idx], buffer);
    idx++;
  }
  *lines_amount = idx;
  return lines;
}
