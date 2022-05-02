/*
 * Usage:
 *		random.out [size] [lmt]
 */

/**
 * @file random.cc
 * @author Jax (jaxvanyang@gmail.com)
 * @brief generate random int array
 * @usage random [-n <size>] -l [<min_val>] [-r <max_val>] [-sh]
 * @default n = 100, l = 1, r = 100, s = false, h = false
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <getopt.h>

inline int random(int mod);
int random(int l, int r);
void help(char *cmd);
void parse_input(int argc, char **argv, int &n, int &l, int &r, bool &s);

int main(int argc, char **argv) {
	srand((unsigned)time(0));

	int n = 100, l = 1, r = 100;
	bool s = false;
	parse_input(argc, argv, n, l, r, s);

	if (n <= 0) {
		std::cerr << "arg error: n = " << n << ", negative n is not allowed" << std::endl;
		exit(EXIT_FAILURE);
	} else if (l > r) {
		std::cerr << "arg error: l = " << l << ", r = " << r << ", cannot set l greater than r" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (s) std::cout << n << std::endl;
	if (n) std::cout << random(l, r);
	for (int i = 1; i < n; ++i) {
		std::cout << ' ' << random(l, r);
	}
	std::cout << std::endl;
}

void help(char *cmd) {
	static char msg[] = 
		"Description: generate random int array\n"
		"Usage: %s [-n <size>] [-l <min_val>] [-r <max_val>] [-sh]\n"
		"	-n	set array size, default is 100\n"
		"	-l	set the min_val, default is 1\n"
		"	-r	set the max_val, default is 100\n"
		"	-s	print array size first\n"
		"	-h	print this message\n";
	printf(msg, cmd);
}

void parse_input(int argc, char **argv, int &n, int &l, int &r, bool &s) {
	const static char optstring[] = "n:l:r:s";
	extern char *optarg;
	int opt;
	while ((opt = getopt(argc, argv, optstring)) != -1) {
		switch (opt) {
			case 'n':
				if (!optarg) {
					help(argv[0]);
					exit(EXIT_FAILURE);
				}
				n = atoi(optarg);
				break;
			case 'l':
				if (!optarg) {
					help(argv[0]);
					exit(EXIT_FAILURE);
				}
				l = atoi(optarg);
				break;
			case 'r':
				if (!optarg) {
					help(argv[0]);
					exit(EXIT_FAILURE);
				}
				r = atoi(optarg);
				break;
			case 's':
				s = true;
				break;
			case 'h':
				help(argv[0]);
				exit(EXIT_SUCCESS);
				break;
			default:
				help(argv[0]);
				exit(EXIT_FAILURE);
		}
	}
}

inline int random(int mod) {
	return (long long) rand() * rand() % mod;
}

int random(int l, int r) {
	return random(r - l + 1) + l;
}
