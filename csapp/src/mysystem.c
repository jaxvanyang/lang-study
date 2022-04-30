/**
 * @file mysystem.c
 * @author Jax (jaxvanyang@gmail.com)
 * @brief Homework 8.22: implement Unix system() function
 * @version 0.1
 * @date 2022-04-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

extern int errno;
extern char **environ;

int mysystem(char *command);

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("Usage: %s [<command> ...]\n", argv[0]);
    return 0;
  }

  int i, ret;
  for (i = 1; i < argc; ++i) {
    ret = mysystem(argv[i]);
    // teminate if one command fails
    if (ret == -1) {
      return ret;
    }
  }

  return 0;
}

int mysystem(char *command) {
  pid_t pid;

  if ((pid = fork()) < 0) {
    fprintf(stderr, "fork error: %s\n", strerror(errno));
    return -1;
  } else if (pid == 0) {
    char *argv[4];
    argv[0] = "/bin/sh";
    argv[1] = "-c";
    argv[2] = command;
    argv[3] = NULL;
    execve(argv[0], argv, environ);
  }

  int status;
  // wait until child process terminates
  while (waitpid(pid, &status, WUNTRACED) < 0) {
    if (errno == EINTR) continue;

    fprintf(stderr, "waitpid error: %s\n", strerror(errno));
    return -1;
  }

  if (WIFEXITED(status)) {
    return WEXITSTATUS(status);
  } else if (WIFSIGNALED(status)) {
    return WTERMSIG(status);
  }

  return 0;
}