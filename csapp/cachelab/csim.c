#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef unsigned char bool_t;

typedef struct {
	int s, b;
	size_t S, E, B;
	bool_t isVerbose;
	FILE *infile;
} Arg;

void init_arg(Arg *const arg) {
	arg->s = arg->S = arg->b = arg->B = arg->E = arg->isVerbose = 0;
	arg->infile = stdin;
}

void print_arg(const Arg *arg) {
	printf("s = %d, S = %ld\nb = %d, B = %ld\nE = %ld\nisVerbose: %d\ninfile = stdin? %d\n",
			arg->s, arg->S, arg->b, arg->B, arg->E, arg->isVerbose, arg->infile == stdin);
}

typedef enum {OK, FAIL, HELP} ParseResult;

ParseResult parse_arg(const int argc, const char *argv[], Arg *arg) {
	if (argc == 1) return FAIL;
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			int n = strlen(argv[i]);
			for (int j = 1; j < n; ++j) {
				switch (argv[i][j]) {
					case 'h':
						return HELP;
					case 'v':
						arg->isVerbose = 1;
						break;
					default:
						if (i + 1 >= argc) return FAIL;

						switch (argv[i][j]) {
							case 's':
								arg->s = atoi(argv[i + 1]);
								arg->S = 1ll << arg->s;
								break;
							case 'E':
								arg->E = atoi(argv[i + 1]);
								break;
							case 'b':
								arg->b = atoi(argv[i + 1]);
								arg->B = 1ll << arg->b;
								break;
							case 't':
								arg->infile = fopen(argv[i + 1], "r");
								break;
							default:
								return FAIL;
						}
						++i;
						j = n;
				}
			}
		} else {
			return FAIL;
		}
	}
	return OK;
}

void help(const char *command) {
	printf("Usage: %s [-hv] -s <s> -E <E> -b <b> -t <trace_file>\n", command);
}

// cache line
typedef struct {
	bool_t v;	// valid bit
	unsigned long tag;
	int t;	// time stamp, used for LRU algorithm
} Line;

Line *init_cache(const size_t S, const size_t E) {
	const size_t size = S * E * sizeof(Line);
	Line *ret = (Line *) malloc(size);
	if (ret) memset(ret, 0, sizeof(size));
	return ret;
}

int xtoi(char ch) {
	ch = tolower(ch);
	int val;
	if (ch >= 'a') {
		val = ch - 'a' + 10;
	} else {
		val = ch - '0';
	}
	if (val < 0 || val > 15) val = 0;
	return val;
}

unsigned long parse_addr(const char *buf) {
	int len = strlen(buf);
	unsigned long addr = 0;
	for (int i = 0; i < len; ++i) {
		addr = (addr << 4) + xtoi(buf[i]);
	}
	return addr;
}

unsigned long get_mask_val(unsigned long addr, unsigned long mask, int offset) {
	return (addr & mask) >> offset;
}

void access_cache(Line *cache, size_t row, size_t E, unsigned long tag, int time, int *hit, int *miss, int *eviction) {
	size_t candidate = 0;	// default candidate is 0
	bool_t isValid = 1;		// assume candidate is valid
	int candiTime = time;	// assume candidate time is current time
	for (size_t i = 0; i < E; ++i) {
		if (cache[row + i].v) {
			if (cache[row + i].tag == tag) {
				// hit & update cache time
				++*hit;
				cache[row + i].t = time;
				return;
			}

			// compare valid candidate
			if (isValid && cache[row + i].t < candiTime) {
				candidate = i;
				candiTime = cache[row + i].t;
			}
		} else if (isValid) {
			// use invalid candidate
			isValid = 0;
			candidate = i;
		}
	}

	// not hit, e.g miss
	++*miss;
	size_t idx = row + candidate;
	// update cache first
	cache[idx].tag = tag;
	cache[idx].t = time;

	if (isValid) {
		// replacing valid line means eviction
		++*eviction;
	} else {
		// mark invalid line as valid
		cache[idx].v = 1;
	}
}

int main(const int argc, const char *argv[]) {
	Arg arg;
	init_arg(&arg);
	ParseResult res = parse_arg(argc, argv, &arg);
	// print_arg(&arg);
	if (res == FAIL) {
		help(argv[0]);
		return res;
	} else if (res == HELP) {
		help(argv[0]);
		return res;
	}

	int s = arg.s, b = arg.b;
	size_t S = arg.S, E = arg.E, B = arg.B;
	int tagSize = 64 - s - b;
	unsigned long tagMask = ((1ll << tagSize) - 1) << (64 - tagSize);
	unsigned long blockMask = B - 1;
	unsigned long setMask = ~(tagMask | blockMask);
	FILE *infile = arg.infile;
	Line *cache = init_cache(S, E);
	if (!cache) {
		perror("Error: allocate cache");
		return FAIL;
	}

	char ops[5], buf[30], addrs[20];
	int size, time = 0;
	int totalHit = 0, totalMiss = 0, totalEviction = 0;
	while (~fscanf(infile, "%1s%29s", ops, buf)) {
		char op = ops[0];
		int bufSize = strlen(buf);
		for (int i = 0; i < bufSize; ++i) {
			if (buf[i] == ',') {
				buf[i] = ' ';
				break;
			}
		}

		sscanf(buf, "%29s%d", addrs, &size);
		unsigned long addr = parse_addr(addrs);

		size_t setIdx = get_mask_val(addr, setMask, b);
		unsigned long tag = get_mask_val(addr, tagMask, b + s);

		int hit = 0, miss = 0, eviction = 0;

		size_t row = setIdx * E;
		switch (op) {
			case 'M':
				access_cache(cache, row, E, tag, time, &hit, &miss, &eviction);
			case 'L':
			case 'S':
				access_cache(cache, row, E, tag, time, &hit, &miss, &eviction);
		}
		totalHit += hit, totalMiss += miss, totalEviction += eviction;

		if (arg.isVerbose) {
			printf("%c %lx,%d", op, addr, size);
			if (miss) printf(" miss");
			if (eviction) printf(" eviction");
			for (int i = 0; i < hit; ++i) {
				printf(" hit");
			}
			puts("");
		}
		
		++time;
	}

	printSummary(totalHit, totalMiss, totalEviction);
	return 0;
}
