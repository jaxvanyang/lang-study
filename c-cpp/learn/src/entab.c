/**
 * replace input's blanks with tabs
 *
 * Exercise 1-21 for K & R
 */

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>

void help_msg(char const* cmd);
void parse_arg(const int argc, char *const argv[],
		int *n, FILE **in);

int main(const int argc, char *const argv[]) {
	int n = 2;
	FILE *in = stdin;

	parse_arg(argc, argv, &n, &in);

	char c;
	int cnt = 0;
	while ((fscanf(in, "%c", &c) != EOF)) {
		switch (c) {
			case ' ':
				++cnt;
				break;
			default:
				for (int i = 0; i < cnt / n; ++i) putchar('\t');
				cnt %= n;
				for (int i = 0; i < cnt; ++i) putchar(' ');
				cnt = 0;
				putchar(c);
		}
	}

	fclose(in);
}

void help_msg(char const* cmd) {
	static char const msg[] =
		"Description: replace input's blankss with tabs\n"
		"Usage: %s -n <blank_cnt> -f <file> -h\n"
		"Default: n = 2, f = stdin\n"
		"Example: %s -n 2 -f a.c\n";
	printf(msg, cmd, cmd);
}

void parse_arg(const int argc, char *const argv[],
		int *n, FILE **in) {
	static char const optstring[] = "n:f:h";
	int c;
	extern char *optarg;

	while ((c = getopt(argc, argv, optstring)) != -1) {
		switch (c) {
			case 'n':
				if (!optarg) help_msg(argv[0]), exit(EXIT_FAILURE);
				*n = atoi(optarg);
				if (*n < 0) {
					perror("Error: negative n is not allowed!");
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
