// lib for O_RDWR and other ways of reading a file
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
  lseek: SEEK_SET; SEEK_CUR; SEEK_END;
*/

static char *filename = "text.txt";

int main(void) {
  int fd = open(filename, O_RDONLY);
  printf("FD: %d\n", fd);
  char buffer[1];
  char c;
  // int readed = read(fd, buffer, 1000);
  // printf("R: %d\n", readed);
  for (int i = 0; i < 20; i++) {
    read(fd, &c, 1);
    write(1, &c, 1);
  }
  lseek(fd, -5, SEEK_CUR);
  printf("\n");

  for (int i = 0; i < 20; i++) {
    read(fd, &c, 1);
    write(1, &c, 1);
  }
  close(fd);
}
