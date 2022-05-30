/**
 * @file cgi_adder.c
 * @author Jax (jaxvanyang@gmail.com)
 * @brief calculate the sum of two query numbers
 * @version 0.1
 * @date 2022-05-29
 * @source code/netp/tiny/cgi-bin/adder.c
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "csapp.h"

int main() {
  char *buf, *p;
  char content[MAXLINE];
  int n1 = 0, n2 = 0;

  // EXtract the two arguments
  if ((buf = getenv("QUERY_STRING")) != NULL) {
    p = strchr(buf, '&');
    if (p) {
      *p = '\0';
      n1 = atoi(buf);
      n2 = atoi(p + 1);
    }
  }

  // Make the response body
  sprintf(content,
          "Welcome to add.com: THE Internet addition portal.\r\n<p>"
          "The answer is: %d + %d = %d\r\n<p>"
          "Thanks for visiting!\r\n",
          n1, n2, n1 + n2);

  // Generate the HTTP response
  printf("Connection: close\r\n");
  printf("Content-length: %ld\r\n", strlen(content));
  printf("Content-type: text/html\r\n\r\n");
  printf("%s", content);
  fflush(stdout);

  return 0;
}