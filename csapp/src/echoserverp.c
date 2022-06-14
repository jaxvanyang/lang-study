/**
 * @file echoserverp.c
 * @author Jax (jaxvanyang@gmail.com)
 * @brief Concurrent echo server based on processes
 * @version 0.1
 * @date 2022-06-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "csapp.h"

void echo(int connfd);
void sigchld_handler(int sig);

int main(int argc, char **argv) {
  int listenfd, connfd;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  Signal(SIGCHLD, sigchld_handler);
  listenfd = Open_listenfd(argv[1]);
  while (1) {
    clientlen = sizeof(struct sockaddr_storage);
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    if (Fork() == 0) {
      Close(listenfd);
      echo(connfd);
      Close(connfd);
      exit(0);
    }
    Close(connfd);
  }
}

void echo(int connfd) {
  size_t n;
  char buf[MAXLINE];
  rio_t rio;

  Rio_readinitb(&rio, connfd);
  while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
    printf("server received %ld bytes\n", n);
    Rio_writen(connfd, buf, n);
  }
}

void sigchld_handler(int sig) {
  while (waitpid(-1, NULL, WNOHANG | WUNTRACED) > 0)
    ;
}