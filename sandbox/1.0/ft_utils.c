#include "libs.h"
#include <stdlib.h>

int ft_strlen(char *str) {
  int len = 0;
  while (str[len])
    len++;
  return (len);
}

char *ft_concat(char *str_a, char *str_b) {
  int size_a = ft_strlen(str_a);
  int size_b = ft_strlen(str_b);
  int total_size = size_a + size_b + 1;
  char *buffer = malloc(total_size * sizeof(char));
  if (buffer == NULL)
    return NULL;
  int i = 0;
  while (i < size_a) {
    buffer[i] = str_a[i];
    i++;
  }
  i = 0;
  while (i < size_b) {
    buffer[i + size_a] = str_b[i];
    i++;
  }
  buffer[i + size_a] = EOF;
  return buffer;
}

char *ft_find(char *search, char c) {
  int i = 0;
  while (search[i] != '\0') {
    if (search[i] == c)
      return (search + i);
  }
  return (search + i);
}
