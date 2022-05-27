/**
 * @file dd2hex.c
 * @author Jax (jaxvanyang@gmail.com)
 * @brief Homework 11.3: convert dotted-decimal ip address to hex ip address
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
    printf("Usage: %s <dotted-decimal ip address>\n", argv[0]);
    return EXIT_FAILURE;
  }

  int ip, res;
  res = inet_pton(AF_INET, argv[1], &ip);
  if (res == 0) {
    printf("Invalid ip address: %s\n", argv[1]);
    return EXIT_FAILURE;
  } else if (res == -1) {
    perror("inet_pton");
    return EXIT_FAILURE;
  }
  ip = ntohl(ip); // convert to host byte order
  printf("0x%x\n", ip);
}