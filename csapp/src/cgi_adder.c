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
  char *buf, *request_method, *p = NULL;
  char content[MAXLINE];
  long a = 0, b = 0;

  // EXtract the two arguments
  if ((buf = getenv("QUERY_STRING")) != NULL) {
    for (char *iptr = buf; *iptr != '\0'; ++iptr) {
      if (*iptr == '&') {
        *iptr = '\0';
        if (p == NULL) p = iptr + 1;
      } else if (!isdigit(*iptr)) {
        *iptr = ' ';
      }
    }
    a = strtol(buf, NULL, 10);
    if (p) b = strtol(p, NULL, 10);
  }

  // Make the response body
  sprintf(content,
          "Welcome to add.com: THE Internet addition portal.\r\n<p>"
          "The answer is: %ld + %ld = %ld\r\n<p>"
          "Thanks for visiting!\r\n",
          a, b, a + b);

  // Generate the HTTP response
  printf("Connection: close\r\n");
  printf("Content-length: %ld\r\n", strlen(content));
  printf("Content-type: text/html\r\n\r\n");
  if ((request_method = getenv("REQUEST_METHOD")) &&
      !strcasecmp(request_method, "HEAD")) {
    fflush(stdout);
    return 0;
  }
  printf("%s", content);
  fflush(stdout);

  return 0;
}