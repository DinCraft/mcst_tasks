#include "sorting.h"
#include <string.h>

int plain(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b);
}
int rplain(const void *a, const void *b) {
  return lex(b, a);
}
int lex(const void *a, const void *b) {
  const char *s1 = *(const char **)a;
  const char *s2 = *(const char **)b;
  for (int i = 0; i < 256; i++) {
    char c1 = s1[i];
    // cast lower case to upper case
    if (c1 >= 0x61 && c1 <= 0x7a) {
      c1 -= 0x0020;
    }
    char c2 = s2[i];
    if (c2 >= 0x61 && c2 <= 0x7a) {
      c2 -= 0x0020;
    }
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
int rlex(const void *a, const void *b) {
  return plain(b, a);
}
