/**
 * replace tab with '\t', backslash with '\\', bacespace with '\b'
 * HINT: use "Ctrl + Backspace" to input backspace
 */

#include <stdio.h>

int main() {
	int c;

	const static char tab[] = "\\t";
	const static char backslash[] = "\\\\";
	const static char backspace[] = "\\b";

	while ((c = getchar()) != EOF) {
		if (c == '\t') printf(tab);
		else if (c == '\\') printf(backslash);
		else if (c == '\b') printf(backspace);
		else putchar(c);
	}
}
