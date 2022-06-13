/**
 * A example of using getopt() to parse command arguments
 */

#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef MY_DEBUG
#define MY_DEBUG 0
#endif

static void print_help_msg(const char *cmd) {
	const static char help_msg[] =
		"Description: print specific string for specific times\n"
		"Usage: %s -h -v -t <time> -c[upper|lower] <string>\n"
		"Example: %s -t 3 -cupper \"hello world\"\n";
	printf(help_msg, cmd, cmd);
}

static void help_exit(const char *cmd, int status) {
	print_help_msg(cmd);
	exit(status);
}

static int is_number(const char *str) {
	size_t len = strlen(str);
	for (size_t i = 0; i < len; ++i) {
		if (!isdigit(str[i])) return 0;
	}
	return 1;
}

int main(const int argc, char *const argv[]) {
	const static int DEFAULT = 0, UPPER = 1, LOWER = 2;
	int opt, time = 0;
	int case_type = 0, is_verbose = 0;
	char *s = NULL;

	/**
	 * optstring only contains short option specifications.
	 * getopt use colon ':' to specific option type
	 * followed by no colon means no argument, e.g., "-h" and "-v"
	 * followed by one colon means a mandatory argument, e.g., "-t <time>"
	 * followed by two colons means an optional argument, e.g., "-c[upper|lower]"
	 */
	const char optstring[] = "ht:c::v";

	// getopt will return -1 if there is no more option
	// return option character otherwise
	while (~(opt = getopt(argc, argv, optstring))) {
		switch (opt) {
			case 'h':
				if (MY_DEBUG) printf("option %c, optarg = %s\n",
						opt, optarg ? optarg : "NULL");
				help_exit(argv[0], EXIT_SUCCESS);
			case 't':
				if (MY_DEBUG) printf("option %c, optarg = %s\n",
						opt, optarg ? optarg : "NULL");
				// optarg will be the next arg after the option
				if (optarg == NULL || !is_number(optarg)) help_exit(argv[0], EXIT_FAILURE);
				time = atoi(optarg);
				break;
			case 'c':
				// optarg will be the remaining string of the option
				// for example, option: "-cupper", optarg: "upper"
				if (MY_DEBUG) printf("option %c, optarg = %s\n",
						opt, optarg ? optarg : "NULL");
				if (optarg == NULL) {
					case_type = DEFAULT;
				} else if (!strcmp(optarg, "upper")) {
					case_type = UPPER;
				} else if (!strcmp(optarg, "lower")) {
					case_type = LOWER;
				} else {
					help_exit(argv[0], EXIT_FAILURE);
				}
				break;
			case 'v':
				if (MY_DEBUG) printf("option %c, optarg = %s\n",
						opt, optarg ? optarg : "NULL");
				is_verbose = 1;
				break;
			default:	// opt will be '?' when encounter unknow option
				if (MY_DEBUG) printf("option %c, optarg = %s\n",
						opt, optarg ? optarg : "NULL");
				help_exit(argv[0], EXIT_FAILURE);
		}
	}

	if (is_verbose) {
		printf("opt = %d, time = %d, case_type = %d, is_verbose = %d\n",
				opt, time, case_type, is_verbose);
	}

	if (optind != argc - 1) {
		help_exit(argv[0], EXIT_FAILURE);
	}

	int len = strlen(argv[optind]);
	s = (char *) malloc((len + 1) * sizeof(char));
	strcpy(s, argv[optind]);

	switch (case_type) {
		case 1:	// UPPER
			for (int i = 0; i < len; ++i) s[i] = toupper(s[i]);
			break;
		case 2:	// LOWER
			for (int i = 0; i < len; ++i) s[i] = tolower(s[i]);
			break;
	}

	while (time--) {
		printf("%s\n", s);
	}
}
