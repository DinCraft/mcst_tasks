#ifndef MATRIX_H
#define MATRIX_H

struct matrix {
  int data[100][100];
};

void fill_matrix(struct matrix *m, int initial_value);

void multiply_matrix(struct matrix *m1, struct matrix *m2, struct matrix *result);

#endif // MATRIX_H
