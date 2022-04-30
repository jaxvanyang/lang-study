#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

extern int errno;

void sigint_handler(int sig);
unsigned int snooze(unsigned int secs);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <sces>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

  if (signal(SIGINT, sigint_handler) == SIG_ERR) {
    fprintf(stderr, "signal error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  snooze(atoi(argv[1]));
}

void sigint_handler(int sig) { return; }

unsigned int snooze(unsigned int secs) {
  unsigned int rem = sleep(secs);
  printf("Slept for %d of %d secs.\n", secs - rem, secs);
  return rem;
}