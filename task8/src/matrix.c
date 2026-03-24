#include "matrix.h"
#include "unistd.h"

int result_row = 0, result_column = 0, iter_index = 0;

void fill_matrix(struct matrix *m, int initial_value) {
  for (int x = 0; x < 100; x++) {
    for (int y = 0; y < 100; y++) {
      m->data[x][y] = initial_value + x;
    }
  }
}

void multiply_matrix(struct matrix *m1, struct matrix *m2, struct matrix *result) {
  for (int x = 0; x < 100; x++) {
    for (int y = 0; y < 100; y++) {
      result_column = x;
      result_row = y;
      result->data[x][y] = 0;
      for (int i = 0; i < 100; i++) {
        iter_index = i;
        result->data[x][y] += m1->data[x][i] * m2->data[i][y];
      }
      usleep(500 * 1000);
    }
  }
}
