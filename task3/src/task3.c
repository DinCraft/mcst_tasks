#include "stdio.h"
#include <stdlib.h>
#include <string.h>

int lex(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b);
}
int rlex(const void *a, const void *b) {
  return lex(b, a);
}
int plain(const void *a, const void *b) {
  const char *s1 = *(const char **)a;
  const char *s2 = *(const char **)b;
  for (int i = 0; i < 256; i++) {
    char c1 = s1[i];
    char c2 = s2[i];
    if (c1 == c2) {
      if (c1 == '\n') {
        return 0;
      }
    }
    else {
      return c1 > c2 ? 1 : -1;
    }
  }
  // unreachable, i guess
  return 0;
}
int rplain(const void *a, const void *b) {
  return plain(b, a);
}

char **input(FILE *input_file, int *lines_amount);

void output(char **lines, int *lines_amount, const char *ouput_name);

int main(int argc, char *argv[])
{
  if (argc != 4) {
    printf("Error: 3 args required - input.txt output.txt <sorting_method>\n");
    printf("<sorting_method> : plain, rplain, lex, rlex\n");
    return -1;
  }
  const char *input_name = argv[1];
  const char *output_name = argv[2];
  FILE *input_file = fopen(input_name, "r");
  if (input_file == NULL) {
    printf("Error: file '%s' not found!\n", input_name);
    return -1;
  }
  int lines_amount;
  char **lines = input(input_file, &lines_amount);
  fclose(input_file);
  qsort(lines, lines_amount, sizeof(char*), plain);
  output(lines, &lines_amount, output_name);
  return 0;
}

void output(char **lines, int *lines_amount, const char *ouput_name) {
  FILE *output_file = fopen(ouput_name, "w");
  if (output_file == NULL) return;
  for (int i = 0; i < *lines_amount; i++) {
    fputs(lines[i], output_file);
  }
  fclose(output_file);
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
