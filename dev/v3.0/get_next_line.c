/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparola <fabricio.parola@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:02:18 by fparola           #+#    #+#             */
/*   Updated: 2025/09/10 18:02:18 by fparola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

int f_strlen(char *buffer) {
  int i;
  if (buffer == NULL)
    return (0);
  i = 0;
  while (buffer[i])
    i++;
  return (i);
}

char *f_search(char *buffer, char c) {
  int i;
  if (buffer == NULL)
    return (NULL);
  i = 0;
  while (buffer[i]) {
    if (buffer[i] == c)
      return (buffer + i);
    i++;
  }
  if (c == '\0')
    return (buffer + i);
  return (NULL);
}

void *f_calloc(size_t count, size_t size) {
  void *p;
  size_t i;

  p = malloc(count * size);
  if (p == NULL)
    return (NULL);
  i = 0;
  while (i < count) {
    ((unsigned char *)p)[i] = 0;
    i++;
  }
  return (p);
}

char *f_strlcpy(char *buffer, char *chunk, size_t size) {
  size_t i;

  i = 0;
  while (chunk[i] && i < (size - 1)) {
    buffer[i] = chunk[i];
    i++;
  }
  buffer[i] = 0;
  return (buffer);
}

char *f_concat(char *buffer, char *chunk) {
  int i;
  int size_b;
  int size_c;
  char *concat_b;

  size_b = f_strlen(buffer);
  size_c = f_strlen(chunk);
  concat_b = f_calloc((size_b + size_c + 1), sizeof(char));
  if (concat_b == NULL)
  {
    free(chunk);
    return (NULL);
  }
  i = 0;
  while (i++ < size_b)
    concat_b[i - 1] = buffer[i - 1];
  i = 0;
  while (i++ < size_c)
    concat_b[(i - 1) + size_b] = chunk[i - 1];
  concat_b[i + size_b - 1] = '\0';
  free(buffer);
  free(chunk);
  return (concat_b);
}

int f_cropidx(char *buffer) {
  int i = 0;
  while (buffer[i]) {
    if (buffer[i] == '\n')
      return (i);
    i++;
  }
  return (i);
}

char *f_cropline(char *buffer, int idx)
{
  if (buffer == NULL)
    return (NULL);

  if (buffer[idx] == '\0') {
    return (buffer);
  }

  char *line = f_calloc(idx + 2, sizeof(char)); 
  if (line == NULL)
    return (NULL);
  int i = 0;
  while (i++ <= idx)
    line[i - 1] = buffer[i - 1];
  line[i] = '\0';
  return (line);
}


char  *f_mvcursor(char *buffer, int idx)
{
  if (buffer != NULL && buffer[idx] == '\0') {
    free(buffer);
    return (NULL);
  }

  int size_r = f_strlen(buffer + (idx + 1));
  if (size_r == 0) {
    return (NULL);
  }

  char *remain = f_calloc(size_r + 1, sizeof(char));

  int i = 0;
  while (i++ < size_r)
    remain[i - 1] = buffer[i + idx];
  remain[i - 1] = '\0'; 

  free(buffer);
  return remain;
}


char *f_cropline2(char *buffer, int idx)
{
  if (buffer == NULL)
    return (NULL);

  if (idx == 0 || buffer[idx] == '\0')
    return (buffer);

  // printf("BUFFER: %s$, IDX: %d\n", buffer, idx + 2);
  char *line = f_calloc((idx + 2), sizeof(char));
  int i = 0;
  while (i++ <= idx)
    line[i - 1] = buffer[i - 1];
  line[i - 1] = '\0';
  return(line);
}

char *get_next_line(int fd)
{
  static char *buffer;
  // printf("--TIMES--\n");

  if (fd == 0)
       return (NULL);
  
  char *chunk = f_calloc(BUFFER_SIZE + 1, sizeof(char));

  if (chunk == NULL) {
    if (buffer != NULL)
      free(buffer);
    return (NULL);
  }
  
  int readed = read(fd, chunk, BUFFER_SIZE);
  if (readed == -1) {
    // free(chunk); // maybe unecessary
    if (buffer != NULL)
      free(buffer);
    return (NULL);
  }
  chunk[readed] = '\0';

  if (readed == 0 && buffer == NULL)
  {
      free(chunk);
      return (NULL);
  }

  buffer = f_concat(buffer, chunk);
  if (readed == 0 || f_search(buffer, '\n') != 0) {
    int cropidx = f_cropidx(buffer);
    char *line = f_cropline2(buffer, cropidx);
    buffer = f_mvcursor(buffer, cropidx);
    return (line);
  } 
  return (get_next_line(fd));
}


// static int l_counter = 0;
// int main()
// {
//   int fd = open(FILE_NAME, O_RDWR);
//   for (l_counter = 1; l_counter <= 5; ++l_counter)
//   {
//     char *l = f_get_next_line(fd);
//     printf("L: %s$\n", l);
//     free(l);
//   }
//   close(fd);
// }
