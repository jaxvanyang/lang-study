/**
 * Remove all comments from input C file
 *
 * Exercise 1-23 for K & R
 */

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>

const static int SOURCE = 0, COMMENT = 1;

void help_msg(char const* cmd);
void parse_arg(const int argc, char *const argv[], FILE **in, int *o);
void parse_input(FILE *in, const int o);

int main(const int argc, char *const argv[]) {
	FILE *in = stdin;
	int o = SOURCE;
	parse_arg(argc, argv, &in, &o);

	parse_input(in, o);

	fclose(in);
}

void help_msg(char const* cmd) {
	static char const msg[] =
		"Description: remove all comments from input C file\n"
		"Usage: %s -f <file> -o[source|comment] -h\n"
		"Default: f = stdin, o = source\n"
		"Example: %s -f a.c -ocomment -c\n";
	printf(msg, cmd, cmd);
}

void parse_arg(const int argc, char *const argv[], FILE **in, int *o) {
	static char const optstring[] = "f:o::h";
	int c;
	extern char *optarg;

	while ((c = getopt(argc, argv, optstring)) != -1) {
		switch (c) {
			case 'f':
				if (!optarg) help_msg(argv[0]), exit(EXIT_FAILURE);
				*in = fopen(optarg, "r");
				if (!*in) help_msg(argv[0]), exit(EXIT_FAILURE);
				break;
			case 'o':
				if (!optarg) help_msg(argv[0]), exit(EXIT_FAILURE);
				if (!strcmp(optarg, "source")) *o = SOURCE;
				else if (!strcmp(optarg, "comment")) *o = COMMENT;
				else help_msg(argv[0]), exit(EXIT_FAILURE);
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

// use DFM to parse input
void parse_input(FILE *in, const int o) {
	char c;
	int status = 0;
	while (~(fscanf(in, "%c", &c))) {
		switch (status) {
			case 0:
				if (c == '"') status = 1;
				else if (c == '\'') status = 2;
				else if (c == '/') status = 5;
				break;
			case 1:
				if (c == '"') status = 0;
				break;
			case 2:
				if (c == '\\') status = 3;
				else status = 4;
				break;
			case 3:
				status = 4;
				break;
			case 4:
				if (c == '\'') {
					status = 0;
				} else {
					perror("Error: expected '");
					exit(EXIT_FAILURE);
				}
				break;
			case 5:
				if (c == '/') status = 6;
				else if (c == '*') status = 8;
				else perror("Error: expected / or *"), exit(EXIT_FAILURE);
				break;
			case 6:
				if (c == '\n') status = 7;
				break;
			case 7:
				if (c == '/') status = 5;
				else status = 0;
				break;
			case 8:
				if (c == '*') status = 9;
				break;
			case 9:
				if (c == '/') status = 7;
				else status = 8;
				break;
			default:
				perror("Error: undifined status");
				exit(EXIT_FAILURE);
		}
		
		if ((o == SOURCE) ^ (status >= 5)) putchar(c);
	}
}
