/**
 * fold long input lines into two or more shorter lines
 * after the last non-blank character that occurs before
 * the n-th column of input.
 *
 * Exercise 1-22 for K & R
 */

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <ctype.h>

void help_msg(char const* cmd);
void parse_arg(const int argc, char *const argv[],
		int *n, int *t, FILE **in);

int main(const int argc, char *const argv[]) {
	int n = 10, t = 6;
	FILE *in = stdin;

	parse_arg(argc, argv, &n, &t, &in);

	char c;
	int cnt = 0, is_begin = 0;
	while ((fscanf(in, "%c", &c) != EOF)) {
		if (is_begin && isblank(c)) continue;
		putchar(c);
		is_begin = 0;
		switch (c) {
			case '\n':
				cnt = 0;
				break;
			case '\t':
				cnt += 4;
				break;
			default:
				++cnt;
		}
		if (cnt >= n) {
			putchar('\n');
			cnt = 0;
			is_begin = 1;
		}
	}

	fclose(in);
}

void help_msg(char const* cmd) {
	static char const msg[] =
		"Description: fold input long lines into shorter lines\n"
		"Usage: %s -n <line_length> -t <tab_size> -f <file> -h\n"
		"Default: n = 10, t = 6, f = stdin\n"
		"Example: %s -n 10 -t 6 -f a.c\n";
	printf(msg, cmd, cmd);
}

void parse_arg(const int argc, char *const argv[],
		int *n, int *t, FILE **in) {
	static char const optstring[] = "n:t:f:h";
	int c;
	extern char *optarg;

	while ((c = getopt(argc, argv, optstring)) != -1) {
		switch (c) {
			case 'n':
				if (!optarg) help_msg(argv[0]), exit(EXIT_FAILURE);
				*n = atoi(optarg);
				if (*n < 1) {
					perror("Error: line length must be positive!");
					help_msg(argv[0]);
					exit(EXIT_FAILURE);
				}
				break;
			case 't':
				if (!optarg) help_msg(argv[0]), exit(EXIT_FAILURE);
				*t = atoi(optarg);
				if (*t < 1) {
					perror("Error: tab size must be positive!");
					help_msg(argv[0]);
					exit(EXIT_FAILURE);
				}
				break;
			case 'f':
				if (!optarg) help_msg(argv[0]), exit(EXIT_FAILURE);
				*in = fopen(optarg, "r");
				if (!*in) help_msg(argv[0]), exit(EXIT_FAILURE);
				break;
			case 'h':
				help_msg(argv[0]);
				exit(EXIT_SUCCESS);
				break;
			default:
				help_msg(argv[0]);
				exit(EXIT_FAILURE);
		}
	}
}
