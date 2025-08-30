#include "libs.h"

int ft_strlen(const char *str) {
  if (!str)
    return 0;
  int len = 0;
  while (str[len])
    len++;
  return (len);
}

char *ft_search(char *s, char c) {
  if (!s)
    return NULL;
  while (*s) {
    if (*s == c)
      return s;
    s++;
  }
  return (NULL);
}

size_t ft_strlcpy(char *dst, const char *src, size_t n) {
  size_t i;
  size_t s_len;

  s_len = ft_strlen(src);
  if (n == 0)
    return (s_len);
  i = 0;
  while (i < n - 1 && src[i]) {
    dst[i] = src[i];
    i++;
  }
  dst[i] = 0;
  return (s_len);
}
