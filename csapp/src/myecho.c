#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
  int i;
  puts("Command-line arguments:");
  for (i = 0; argv[i]; ++i) {
    printf("    argv[%2d]: %s\n", i, argv[i]);
  }

  puts("Environment variables:");
  for (i = 0; envp[i]; ++i) {
    printf("    envp[%2d]: %s\n", i, envp[i]);
  }
}