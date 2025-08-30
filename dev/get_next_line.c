#include "./get_next_line_utils.c"
#include "./libs.h"
#include <fcntl.h>
#include <stdio.h>

#define BUFFER_SIZE 28
static char *F_BUFFER;
static char *F_NAME = "../misc/text_1.txt";

void panic(char *s) { printf("\n[ERROR] - %s\n", s); }

char *ft_concat(char *chunk) {
  int size_c = ft_strlen(chunk);
  int size_o = ft_strlen(F_BUFFER);
  char *buffer = malloc((size_c + size_o + 1) * sizeof(char));
  int i = 0;
  while (i < size_o) {
    buffer[i] = F_BUFFER[i];
    i++;
  }
  i = 0;
  while (i < size_c) {
    buffer[i + size_o] = chunk[i];
    i++;
  }
  buffer[i + size_o] = '\0';
  free(F_BUFFER);
  free(chunk);
  return buffer;
}

char *ft_cropline() {
  if (!F_BUFFER)
    return (NULL);
  int i = 0;
  while (F_BUFFER[i] && F_BUFFER[i] != '\n')
    i++;
  char *line_buffer = malloc((i + 1) * sizeof(char));
  ft_strlcpy(line_buffer, F_BUFFER, i + 1);
  return (line_buffer);
}

void ft_setcursor(char *remaining) {
  int size_r = ft_strlen(remaining);
  char *buffer = malloc((size_r) * sizeof(char));
  ft_strlcpy(buffer, remaining, size_r + 1);
  free(F_BUFFER);
  F_BUFFER = buffer;
}

char *ft_get_next_line(int fd) {
  char *chunk = malloc(BUFFER_SIZE * sizeof(char));
  if (!chunk)
    return (NULL);

  int r_bytes = read(fd, chunk, BUFFER_SIZE);
  if (!r_bytes)
    return (NULL);
  if (r_bytes == -1)
    panic("reading file");

  F_BUFFER = ft_concat(chunk);
  char *p_linebreak = ft_search(chunk, '\n');
  if (p_linebreak) {
    char *line = ft_cropline();
    ft_setcursor(p_linebreak + 1);
    return line;
  }

  return (ft_get_next_line(fd));
}

int main(void) {
  int fd = open(F_NAME, O_RDWR);
  for (int i = 1; i <= 10; i++) {
    char *l = ft_get_next_line(fd);
    // printf("L: %s\n", l);
    // printf("B: %s\n", F_BUFFER);
    free(l);
  }
  free(F_BUFFER);
  close(fd);
}
