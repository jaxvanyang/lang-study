#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>

int hex2dec_char(char ch) {
	ch = tolower(ch);
	return isdigit(ch) ? ch - '0' : ch - 'a' + 10;
}

int8_t *parse_hex(char *s) {
	int len = strlen(s);
	int8_t *ret = malloc(32);
	memset(ret, 0, 32);

	for (int i = 0; i < len; ++i) {
		int p = len - 1 - i;
		int val = hex2dec_char(s[p]);

		for (int j = 0; j < 4; ++j) {
			ret[i * 4 + j] = (val >> j) & 1;
		}
	}

	return ret;
}

int hex2dec(char *s) {
	int8_t *bits = parse_hex(s);

	// for (int i = 0; i < 8; ++i) {
	// 	for (int j = 0; j < 4; ++j) {
	// 		printf("%d", bits[i * 4 + j]);
	// 	}

	// 	putchar(' ');
	// }
	// puts("");

	int ret = INT32_MIN * bits[31];

	for (uint8_t i = 0; i < 31; ++i) {
		ret += bits[i] * (1 << i);
	}

	return ret;
}

int main() {
	char s[8];

	puts("Input: 1~8 hex charactors\n"
		 "Output: signed decimal value");

	while (scanf("%s", s) > 0) {
		printf("%d\n", hex2dec(s));
	}
}
