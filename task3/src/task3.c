#include "stdio.h"
#include "sorting.h"
#include <stdlib.h>
#include <string.h>

char **input(FILE *input_file, int *lines_amount);

int output(char **lines, int *lines_amount, const char *ouput_name);

int main(int argc, char *argv[])
{
  if (argc != 4) {
    printf("Error: 3 args required - input.txt output.txt <sorting_method>\n");
    printf("<sorting_method> : plain, rplain, lex, rlex\n");
    return -1;
  }
  const char *input_name = argv[1];
  const char *output_name = argv[2];
  const char *sorting_method = argv[3];
  int (*sm)(const void *, const void *);
  // selecting sorting method
  if (strcmp(sorting_method, "plain") == 0) {
    sm = plain;
  }
  else if (strcmp(sorting_method, "rplain") == 0) {
    sm = rplain;
  }
  else if (strcmp(sorting_method, "lex") == 0) {
    sm = lex;
  }
  else if (strcmp(sorting_method, "rlex") == 0) {
    sm = rlex;
  }
  else {
    printf("Error: incorrect sorting method!\n");
    printf("<sorting_method> : plain, rplain, lex, rlex\n");
    return -1;
  }
  FILE *input_file = fopen(input_name, "r");
  if (input_file == NULL) {
    printf("Error: file '%s' not found!\n", input_name);
    return -1;
  }
  int lines_amount;
  char **lines = input(input_file, &lines_amount);
  fclose(input_file);
  qsort(lines, lines_amount, sizeof(char*), sm);
  int result = output(lines, &lines_amount, output_name);

  // cleanup
  for (int i = 0; i < lines_amount; i++) {
    free(lines[i]);
  }
  free(lines);

  if (result == -1) {
    printf("Error while writing to file!\n");
    return -1;
  }
  return 0;
}

int output(char **lines, int *lines_amount, const char *ouput_name) {
  FILE *output_file = fopen(ouput_name, "w");
  if (output_file == NULL) return -1;
  for (int i = 0; i < *lines_amount; i++) {
    fputs(lines[i], output_file);
  }
  fclose(output_file);
  return 0;
}

char **input(FILE *input_file, int *lines_amount) {
  char buffer[256];
  int array_size = 4;
  char **lines = malloc(sizeof(char*) * array_size);
  if (lines == NULL) return NULL;
  int idx = 0;
  while (fgets(buffer, 256, input_file) != NULL) {
    int empty = 1;
    // check if empty
    for (int i = 0; i < 256; i++) {
      if (buffer[i] == '\n') break;
      if (buffer[i] != ' ') empty = 0;
    }
    if (!empty) {
      if (idx == array_size) {
        array_size *= 2;
        char **temp = realloc(lines, sizeof(char*) * array_size);
        if (temp != NULL) lines = temp;
      }
      lines[idx] = malloc(sizeof(char) * 256);
      strcpy(lines[idx], buffer);
      idx++;
    }
  }
  *lines_amount = idx;
  return lines;
}
