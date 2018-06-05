#include <stdio.h>
#include <string.h>
#include "malloc_j.h"

int main() {
  init();
  char* foo = malloc_j(200 * MiB);
  strcpy(foo, "ABCDEFGHIJ");
  foo[10] = '\0';
  char* bar = malloc_j(200 * MiB);
  strcpy(bar, "KLMNOPQRST");
  bar[10] = '\0';
  char* baz = malloc_j(99 * MiB);
  strcpy(baz, "UVWXYZ");
  baz[10] = '\0';
  printf("%s%s%s\n", foo, bar, baz);
  cleanup();
  return 0;
}
