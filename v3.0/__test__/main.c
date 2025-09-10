#include "../get_next_line.h"

void __T1__f_cropidx() {
  char *b = "onetwo";
  size_t crop_idx = f_cropidx(b);
  printf("R: %lu\n", crop_idx);
}

void __T2__f_cropidx() {
  char *b = "one\ntwo";
  size_t crop_idx = f_cropidx(b);
  printf("R: %lu\n", crop_idx);
}

void __T1__f_mvcursor() {
  // if buffer + idx is NULL
  char *b = malloc(6);
  f_strlcpy(b, "seven", 6);
  printf("S: %s$\n", b);
  int c = f_cropidx(b);
  printf("CROP: %d\n", c);
  char *r = f_mvcursor(b, 2);
  printf("R: %s\n", r);
  free(r);
  free(b);
  // f_mvcursor(b, 0);
}

/* f_extract */
void __T1__f_extract() {
  char *b = "vanidog";
  char *e = f_extract(b, 2);
  printf("e: %c\n", *(b + 2));
  printf("e: %s\n", e);
  free(e);
}

int main() {
  __T1__f_cropidx();
  __T2__f_cropidx();
}
