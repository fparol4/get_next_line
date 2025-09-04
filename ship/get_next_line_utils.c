#include "get_next_line.h"

void panic(char *s) { printf("\n[ERROR] - %s\n", s); exit(1); }

int f_strlen(const char *str)
{
	int len;
 
	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char *f_search(char *s, char c) {
  if (!s)
    return NULL;
  while (*s) {
    if (*s == c)
      return s;
    s++;
  }
  return (NULL);
}

char *f_concat(char *original, char *chunk)
{
	int   i;
	int   size_o;
	int   size_c;
	char  *buffer;

	size_o = f_strlen(original); 
	size_c = f_strlen(chunk); 
	buffer = malloc((size_o + size_c + 1) * sizeof(char));

	if (!buffer)
		return (NULL);

	i = 0;
	while (i < size_o)
	{
		buffer[i] = original[i];
		i++;
	}
	

	i = 0;
	while (i < size_c)
	{
		buffer[i + size_o] = chunk[i];
		i++;
	}
	
	buffer[i + size_o] = '\0';
	free(original);
	free(chunk);
	return buffer;
}

size_t f_strlcpy(char *dst, const char *src, size_t n) {
  size_t i;
  size_t s_len;

  s_len = f_strlen(src);
  if (n == 0)
    return (s_len);
  i = 0;
  while (i < n - 1 && src[i]) {
    dst[i] = src[i];
    i++;
  }
  dst[i] = '\0';
  return (s_len);
}
