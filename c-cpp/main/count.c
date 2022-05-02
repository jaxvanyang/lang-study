/**
 * count blanks, tabs and newlines
 */

#include <stdio.h>

// TODO: use command arguments
int main() {
	int c;
	int bc = 0, tc = 0, nc = 0;

	while ((c = getchar()) != EOF) {
		switch (c) {
			case ' ':
				++bc;
				break;
			case '\t':
				++tc;
				break;
			case '\n':
				++nc;
				break;
		}
	}

	printf("blanks: %d, tabs: %d, newlines: %d\n", bc, tc, nc);
}
