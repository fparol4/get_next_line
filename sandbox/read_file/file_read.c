// lib for O_RDWR and other ways of reading a file
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
  OPEN: O_APPEND; O_CREAT; O_RDWR, O_RDONLY, O_WRONLY;
*/

static char *filename = "text.txt";

int main(void) {
  int fd = open(filename, O_RDONLY);
  printf("FD: %d\n", fd);
  char buffer[1];
  char c;
  // int readed = read(fd, buffer, 1000);
  // printf("R: %d\n", readed);
  while (read(fd, &c, 1)) {
    write(1, &c, 1);
    // printf("%c", c);
  }
  close(fd);
}
