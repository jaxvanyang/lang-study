/**
 * @file hello_mmap.c
 * @author Jax (jaxvanyang@gmail.com)
 * @brief Homework 9.14: uses mmap to translate 'H' to 'J' in a file
 * @version 0.1
 * @date 2022-05-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <sys/mman.h>
#include <unistd.h>

#include "csapp.h"

int main(int argc, char **argv) {
  struct stat stat;
  int fd;
  
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  fd = Open(argv[1], O_RDWR, 0);
  fstat(fd, &stat);

  char *bufp = Mmap(NULL, stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  for (off_t i = 0; i < stat.st_size; ++i) {
    if (bufp[i] == 'H') {
      bufp[i] = 'J';
    }
  }

  Munmap(bufp, stat.st_size);
  return 0;
}