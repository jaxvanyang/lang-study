/**
 * @file hostinfo.c
 * @author Jax (jaxvanyang@gmail.com)
 * @brief Homework 11.4: retrieve ip addresses from the domain name
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "csapp.h"

int main(int argc, char **argv) {
  struct addrinfo *p, *listp, hints;
  char buf[MAXLINE];
  int rc;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <domain name>\n", argv[0]);
    return 0;
  }

  // Get a list of addrinfo records
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;        // IPv4 only
  hints.ai_socktype = SOCK_STREAM;  // Connection only
  if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rc));
    return 0;
  }

  // Walk the list and display each IP address
  // flags = NI_NUMERICHOST; // Display address string instead of domain name
  for (p = listp; p; p = p->ai_next) {
    // Getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
    inet_ntop(p->ai_family, &((struct sockaddr_in *)p->ai_addr)->sin_addr, buf, sizeof(buf));
    puts(buf);
  }

  // Clean up
  Freeaddrinfo(listp);

  return 0;
}