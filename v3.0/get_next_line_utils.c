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

char *f_concat(char *buffer, char *chunk) {
  int i;
  int size_b;
  int size_c;
  char *concat_b;

  if (chunk == NULL)
    return (buffer);
  size_b = f_strlen(buffer);
  size_c = f_strlen(chunk);
  if (size_b == 0 && size_b == size_c)
    return (NULL);
  concat_b = f_calloc((size_b + size_c + 1), sizeof(char));
  if (concat_b == NULL)
    return (NULL);
  i = 0;
  while (i++ < size_b)
    concat_b[i - 1] = buffer[i - 1];
  i = 0;
  while (i++ < size_c)
    concat_b[(i - 1) + size_b] = chunk[i - 1];
  concat_b[i + size_b - 1] = '\0';
  return (concat_b);
}

char *f_strlcpy(char *buffer, char *chunk, size_t size) {
  size_t i;
  size_t chunk_s;

  i = 0;
  while (chunk[i] && i < (size - 1)) {
    buffer[i] = chunk[i];
    i++;
  }
  buffer[i] = 0;
  return (buffer);
}
