/**
 * split input to one word per line
 */

#include <stdio.h>
#include <ctype.h>

int main() {
	int c;
	int in_word = 0;

	while ((c = getchar()) != EOF) {
		if (isspace(c)) {
			if (in_word) putchar('\n');
			in_word = 0;
		} else {
			in_word = 1;
			putchar(c);
		}
	}
}
