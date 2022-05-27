/**
 * @file hex2dd.c
 * @author Jax (jaxvanyang@gmail.com)
 * @brief Homework 11.2: convert hex ip address to dotted-decimal ip address
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <hex ip address>\n", argv[0]);
    return EXIT_FAILURE;
  }

  int ip;
  sscanf(argv[1], "%x", &ip);
  ip = htonl(ip); // convert to network byte order
  if (errno == ERANGE) {
    perror("strtol");
    return EXIT_FAILURE;
  }

  char ip_str[INET_ADDRSTRLEN];
  if (!inet_ntop(AF_INET, &ip, ip_str, sizeof(ip_str))) {
    perror("inet_ntop");
    return EXIT_FAILURE;
  }
  puts(ip_str);
  return 0;
}