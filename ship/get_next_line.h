#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

// #libs
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// #utils
void	panic(char *s);
int		f_strlen(const char *str);
char	*f_search(char *s, char c);
char	*f_concat(char *original, char *chunk);
size_t	f_strlcpy(char *dst, const char *src, size_t n);

#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif
