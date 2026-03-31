#include "array_alg.h"
#include <stdio.h>

void test1();

void maxlen_and_count_test(int array[], int size, int exp_maxlen, int exp_count);

void alg_test(int array[], int size, int exp[]);

void print_array(int array[], int size);

int test_id = 0;

int main(int argc, char *argv[]) {
{
  int array[] = {1,2,3,4,5};
  int size = 5;
  int exp_maxlen = 5;
  int exp_count = 1;
  maxlen_and_count_test(array, size, exp_maxlen, exp_count);
}
{
  int array[] = {0,1,2,3,0};
  int size = 5;
  int exp_maxlen = 4;
  int exp_count = 1;
  maxlen_and_count_test(array, size, exp_maxlen, exp_count);
}
{
  int array[] = {1,2,3,0,4,5,6,0};
  int size = 8;
  int exp_maxlen = 4;
  int exp_count = 1;
  maxlen_and_count_test(array, size, exp_maxlen, exp_count);
}
{
  int array[] = {1,2,3,0,4,5,6};
  int size = 7;
  int exp[] = {0,4,5,6};
  alg_test(array, size, exp);
}
{
  int array[] = {1,2,3,0,0,4,5,6};
  int size = 8;
  int exp[] = {0,4,5,6};
  alg_test(array, size, exp);
}
{
  int array[] = {1,2,3,0,0,4,5,6,3};
  int size = 9;
  int exp[] = {0,4,5,6};
  alg_test(array, size, exp);
}
{
  int array[] = {1,2,3,0,0,4,5,6,3,8};
  int size = 9;
  int exp[] = {0,4,5,6};
  alg_test(array, size, exp);
}
{
  int array[] = {0,1,2,3,0,0,8};
  int size = 7;
  int exp[] = {0,1,2,3};
  alg_test(array, size, exp);
}
{
  int array[] = {0,1,2,3,0,0,2,4,6};
  int size = 9;
  int exp[] = {0,2,4,6};
  alg_test(array, size, exp);
}
{
  int array[] = {0,1,2,3,4,0,2,4,6};
  int size = 9;
  int exp[] = {0,1,2,3,4};
  alg_test(array, size, exp);
}
  return 0;
}

void print_array(int array[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
}

void alg_test(int array[], int size, int exp[]) {
  int i1, i2;
  get_subsequence(array, size, &i1, &i2);
  for (int i = 0; i < i2 - i1; i++) {
    if (exp[i] != array[i + i1]) {
      printf("test %d:\n", test_id);
      print_array(array, size);
      printf("\n");
      break;
    }
  }
  test_id++;
}

void maxlen_and_count_test(int array[], int size, int exp_maxlen, int exp_count) {
  int maxlen = 0;
  int count = 0;
  maxlen_and_count(array, size, &maxlen, &count);
  if (maxlen != exp_maxlen || count != exp_count) {
    printf("test %d:\n", test_id);
    for (int i = 0; i < size; i++) {
      printf("%d ", array[i]);
    }
    printf("\n");
  }
  if (maxlen != exp_maxlen) {
    printf("- (maxlen != exp_maxlen) (%d != %d)\n", maxlen, exp_maxlen);
  }
  if (count != exp_count) {
    printf("- (count != exp_count) (%d != %d)\n", count, exp_count);
  }
  test_id++;
}
