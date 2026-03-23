#include "stdio.h"
#include "syscall.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char **input(FILE *input_file, int *lines_amount);

int thread_function(pid_t *p, const char *input_name);

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
  else {
    thread_function(&p, argv[1]);
  }

  return 0;
}

int thread_function(pid_t *p, const char *input_name) {
  FILE *input_file = fopen(input_name, "r");
  if (input_file == NULL) {
    printf("Error: file '%s' not found!\n", input_name);
    return -1;
  } 
  int lines_amount = 0;
  char **lines = input(input_file, &lines_amount);
  fclose(input_file);

  const char *output_name = "parent_copy";
  if (*p == 0) {
    output_name = "child_copy";
  }
  FILE *output_file = fopen(output_name, "w");
  for (int i = 0; i < lines_amount; i++) {
    fputs(lines[i], output_file);
  }
  fclose(output_file);

  input_file = fopen(output_name, "r");
  if (input_file == NULL) {
    printf("Error: file '%s' not found!\n", input_name);
    return -1;
  } 
  lines_amount = 0;
  lines = input(input_file, &lines_amount);
  if (*p == 0) {
    printf("Child:\n");
  }
  else {
    printf("Parent:\n");
  }
  for (int i = 0; i < lines_amount; i++) {
    printf("%s", lines[i]);
  }
  fclose(input_file);
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
