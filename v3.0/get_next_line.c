/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparola <fabricio.parola@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:56:11 by fparola           #+#    #+#             */
/*   Updated: 2025/09/10 19:54:21 by fparola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

size_t f_cropidx(char *buffer) {
  size_t idx;

  if (buffer == NULL)
    return (0);
  idx = 0;
  while (buffer[idx]) {
    if (buffer[idx] == '\n')
      return (idx + 1);
    idx++;
  }
  return (idx);
}

char *f_mvcursor(char *buffer, int idx) {
  int remain;
  char *remain_b;

  if (buffer == NULL)
    return (NULL);
  remain = f_strlen(buffer + idx);
  if (remain == 0) {
    free(buffer);
    return (NULL);
  }
  remain_b = f_calloc(remain + 1, sizeof(char));
  f_strlcpy(remain_b, buffer + idx, remain + 1);
  return (remain_b);
}

char *f_extract(char *buffer, int idx) {
  char *line_b;

  if (buffer == NULL || idx == 0)
    return (NULL);
  line_b = f_calloc(idx + 2, sizeof(idx));
  if (line_b == NULL)
    return (NULL);
  f_strlcpy(line_b, buffer, idx + 2);
  return (line_b);
}

char *get_next_line(int fd) {
  int readed;
  int crop_idx;
  char *chunk;
  char *line;
  static char *buffer;

  if (fd == 0)
    return (NULL);
  chunk = f_calloc(BUFFER_SIZE + 1, sizeof(char));
  if (chunk == NULL)
    return (NULL);
  readed = read(fd, chunk, BUFFER_SIZE);
  if (readed == -1)
    return (NULL);
  chunk[readed] = '\0';
  // printf("r: %d\n", readed);
  // printf("b: %s\n", buffer);
  buffer = f_concat(buffer, chunk);
  // printf("c: %s\n", chunk);
  // printf("ab: %s\n", buffer);

  if (readed == 0 || f_search(buffer, '\n')) {
    crop_idx = f_cropidx(buffer);
    // printf("ci: %d\n", crop_idx);
    // if (crop_idx == 0) {
    //   free(chunk);
    //   free(buffer);
    //   return (NULL);
    // }
    line = f_extract(buffer, crop_idx);
    buffer = f_mvcursor(buffer, crop_idx);
    printf("rb: %s\n", buffer);
    return (line);
  }
  return (get_next_line(fd));
}

// int main() {
//   int fd = open(FILE_NAME, O_RDWR);
//   for (int i = 1; i <= 3; ++i) {
//     char *l = get_next_line(fd);
//     printf("l: %s$\n", l);
//     free(l);
//   }
//   close(fd);
// }
