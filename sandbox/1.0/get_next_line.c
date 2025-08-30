#include "./ft_utils.c"
#include "libs.h"

#define BUFFER_SIZE 10

static char *filename = "../misc/text.txt";
static char *file_buffer;

char *clean() {
  printf("clear all allocation");
  return NULL;
}

char *ft_strcpy(char *str, int size) {
  char *new_str = malloc((size + 1) * sizeof(char));
  if (new_str == NULL)
    return (NULL);
  int i = 0;
  while (i < size) {
    new_str[i] = str[i];
    i++;
  }
  new_str[i] = '\0';
  return new_str;
}

char *ft_setcursor(char *buffer, int start) {
  int len = ft_strlen(buffer + start);
  char *new_buffer = ft_strcpy(buffer + start, len);
  free(buffer);
  return (new_buffer);
}

char *ft_get_next_line(int fd) {
  char *chunk = malloc(BUFFER_SIZE * sizeof(char));
  if (chunk == NULL)
    return clean();
  int readed = read(fd, chunk, BUFFER_SIZE);
  if (readed == -1)
    return clean();
  char *pt_lbreak = ft_find(file_buffer, '\n');
  if (pt_lbreak == NULL) {
    ft_concat(file_buffer, chunk);
    return ft_get_next_line(fd);
  }
  char *line = ft_strcpy(file_buffer, pt_lbreak - file_buffer);
  ft_setcursor(file_buffer, pt_lbreak - file_buffer);
  return line;
}

int run() {
  int fd = open(filename, O_RDWR);
  printf("FD: %d", fd);
  if (fd == -1)
    return -1;
  char *line = ft_get_next_line(fd);
  // printf("LINE: %s\n", line);
  // return 1;
}

int main(void) { run(); }
