/**
 * @file mmapcopy.c
 * @author Jax (jaxvanyang@gmail.com)
 * @brief Homework 9.5: uses mmap to copy file fd to stdout
 * @version 0.1
 * @date 2022-05-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <csapp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

void mmapcopy(int fd, off_t size);

// mmapcopy driver
int main(int argc, char **argv) {
  struct stat stat;  // store file status
  int fd;            // file descriptor

  if (argc != 2) {
    fprintf(stderr, "usage: %s <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // copy the input argument to stdout
  fd = Open(argv[1], O_RDONLY, 0);
  fstat(fd, &stat);
  mmapcopy(fd, stat.st_size);
  return 0;
}

// map file content to memory
void mmapcopy(int fd, off_t size) {
  char *bufp;  // ptr to memory-mapped VM area

  bufp = Mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
  Write(1, bufp, size);  // write buf to stdout
}