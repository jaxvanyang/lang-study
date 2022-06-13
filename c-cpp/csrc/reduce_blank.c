/**
 * replace multiple consequent blanks with a sigle blank
 */

#include <stdio.h>

int main() {
	int c;
	int is_pre_blank = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			if (!is_pre_blank) putchar(c);
			is_pre_blank = 1;
		} else {
			putchar(c);
			is_pre_blank = 0;
		}
	}
}
