/**
 * replace input's tabs with blanks
 *
 * Exercise 1-20 for K & R
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

	char tab_s[n + 1];
	for (int i = 0; i < n; ++i) tab_s[i] = ' ';
	tab_s[n] = '\0';

	char c;
	while ((fscanf(in, "%c", &c) != EOF)) {
		switch (c) {
			case '\t':
				printf("%s", tab_s);
				break;
			default:
				putchar(c);
		}
	}

	fclose(in);
}

void help_msg(char const* cmd) {
	static char const msg[] =
		"Description: replace input's tabs with blanks\n"
		"Usage: %s -n <tab_size> -f <file> -h\n"
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
				if (*n <= 0) {
					perror("Error: tab size must be positive");
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
