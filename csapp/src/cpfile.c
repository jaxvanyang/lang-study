/**
 * @file cpfile.c
 * @author Jax (jaxvanyang@gmail.com)
 * @brief Homework 10.7, 10.10: use RIO function to copy file to stdout
 * @version 0.1
 * @date 2022-05-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "csapp.h"

int main(int argc, char **argv) {
  char buf[MAXLINE];
  rio_t rio;
  int n;

  if (argc == 2) {
    freopen(argv[1], "r", stdin);
  }

  Rio_readinitb(&rio, STDIN_FILENO);
  while ((n = Rio_readlineb(&rio, buf, MAXBUF)) != 0) {
    Rio_writen(STDOUT_FILENO, buf, n);
  }
}