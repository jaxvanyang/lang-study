/**
 * print a histogram of input word lengths
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

const static int MAX_LEN = 5;

int main() {
	int cnts[MAX_LEN + 2];
	memset(cnts, 0, sizeof(cnts));
	int c, len = 0;
	int max_cnt = 0;

	while ((c = getchar()) != EOF) {
		if (isspace(c)) {
			int idx = len > MAX_LEN ? MAX_LEN + 1 : len;
			++cnts[idx];
			if (idx > 0 && cnts[idx] > max_cnt) {
				max_cnt = cnts[idx];
			}
			len = 0;
		} else {
			++len;
		}
	}

	for (int i = max_cnt; i >= 1; --i) {
		for (int j = 1; j <= MAX_LEN + 1; ++j) {
			if (cnts[j] >= i) printf("  #");
			else printf("   ");
		}
		putchar('\n');
	}

	for (int i = 1; i <= MAX_LEN; ++i) {
		printf("---");
	}
	puts("-------");

	for (int i = 1; i <= MAX_LEN; ++i) {
		printf("%3d", i);
	}
	puts(" others");
}
