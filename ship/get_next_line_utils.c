#include "get_next_line.h"
#include <unistd.h>

void panic(char *s) { printf("[ERROR] - %s\n", s); exit(1); }

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

char *f_concat(char *src, char *add)
{
	int   i;
	int   size_o;
	int   size_c;
	char  *buffer;

	size_o = f_strlen(src);
	size_c = f_strlen(add); 
	printf("SIZE_O: %d, SIZE_C: %d\n", size_o, size_c);

	if (size_c == 0)
		return (NULL);

	buffer = malloc((size_o + size_c + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);

	i = 0;
	while (i < size_o)
	{
		buffer[i] = src[i];
		i++;
	}
	
	i = 0;
	while (i < size_c)
	{
		buffer[i + size_o] = add[i];
		i++;
	}
	
	buffer[i + size_o] = '\0';
	free(src);
	free(add);
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
