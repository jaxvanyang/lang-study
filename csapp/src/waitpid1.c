/**
 * @file waitpid1.c
 * @author Jax (jaxvanyang@gmail.com)
 * @brief Homework 8.24: modify the original waitpid1.c
 * @version 0.1
 * @date 2022-04-30
 *
 * @copyright Copyright (c) 2022
 *
 */

/* $begin waitpid1 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 2

void unix_error(char *msg);
pid_t Fork();

int main() {
  char *s = NULL;
  int status, i;
  pid_t pid;

  /* Parent creates N children */
  for (i = 0; i < N; i++)  // line:ecf:waitpid1:for
    if ((pid = Fork()) == 0) {
      s[i] = i; // write to NULL, arise SIGSEGV
      exit(100 + i);
    }

  /* Parent reaps N children in no particular order */
  while ((pid = waitpid(-1, &status, 0)) > 0) {  // line:ecf:waitpid1:waitpid
    if (WIFEXITED(status)) {                     // line:ecf:waitpid1:wifexited
      printf("child %d terminated normally with exit status=%d\n", pid,
             WEXITSTATUS(status));  // line:ecf:waitpid1:wexitstatus
    } else if (WIFSIGNALED(status)) {
      int sig = WTERMSIG(status);
      fprintf(stderr, "child %d terminated by signal %d: ", pid, sig);
      psignal(sig, NULL);
    } else {
      printf("child %d terminated abnormally\n", pid);
    }
  }

  /* The only normal termination is if there are no more children */
  if (errno != ECHILD)  // line:ecf:waitpid1:errno
    unix_error("waitpid error");

  exit(0);
}
/* $end waitpid1 */

void unix_error(char *msg) {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(EXIT_FAILURE);
}

pid_t Fork() {
  pid_t pid = fork();
  if (pid < 0) unix_error("Fork error");
  return pid;
}