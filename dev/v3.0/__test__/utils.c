#include "../get_next_line.h"

void __T1__f_concat() {
  char *b = f_calloc(3, sizeof(char));
  char *c = f_calloc(3, sizeof(char));
  char *r = f_concat(b, c);
  printf("R: %s\n", r);
  free(b);
  free(c);
  free(r);
}

void __T2__f_concat() {
  char *b = f_calloc(4, sizeof(char));
  f_strlcpy(b, "one", 4);
  char *c = f_calloc(4, sizeof(char));
  f_strlcpy(c, "two", 4);
  char *r = f_concat(b, c);
  printf("B: %s\n", b);
  printf("C: %s\n", c);
  printf("R: %s\n", r);
  free(b);
  free(c);
  free(r);
}

int main() { __T2__f_concat(); }
