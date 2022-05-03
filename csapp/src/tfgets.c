/**
 * @file tfgets.c
 * @author Jax (jaxvanyang@gmail.com)
 * @brief Homework 8.25: same as fgets, but with 5 seconds timeout
 * @version 0.1
 * @date 2022-05-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);

static sigjmp_buf jmpbuf;

void unix_error(char *msg);
sighandler_t Signal(int sig, sighandler_t handler);

void timeout_handler(int sig);

char *tfgets(char *s, int n, FILE *fp);

int main() {
  char buf[100];
  char *sp = tfgets(buf, 100, stdin);
  if (sp == NULL) {
    printf("Log: timeout\n");
  } else {
    printf("%s", buf);
  }

  return 0;
}

void unix_error(char *msg) {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(0);
}

sighandler_t Signal(int sig, sighandler_t handler) {
  struct sigaction action, old_action;

  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = SA_RESTART;

  if (sigaction(sig, &action, &old_action) < 0) unix_error("Signal error");
  return old_action.sa_handler;
}

void timeout_handler(int sig) { siglongjmp(jmpbuf, 1); }

char *tfgets(char *s, int n, FILE *fp) {
  if (!sigsetjmp(jmpbuf, 1)) {
    Signal(SIGALRM, timeout_handler);
    alarm(5);
    s = fgets(s, n, fp);
    alarm(0);
    Signal(SIGALRM, SIG_DFL);
    return s;
  }
  return NULL;
}