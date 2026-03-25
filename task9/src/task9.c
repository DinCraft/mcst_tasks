#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
  struct timeval tv;
  gettimeofday(&tv,NULL);
  unsigned int time_in_micros = 1000000 * tv.tv_sec + tv.tv_usec;
  printf("%d\n", time_in_micros);
  srand(time_in_micros);
  printf("%d\n", rand());
  return 0;
  int size = (int)1e6;
  int array[size];
  for (int i = 0; i < size; i++) {
    array[i] = rand();
  }
  return 0;
}
