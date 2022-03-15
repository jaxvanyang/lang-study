#include <stdio.h>

// replace y's least byte with x's, and return that value
int mix_words(int x, int y) {
	return (x & 0xff) | (y & ~0xff);
}

int main() {
	int x = 0x89ABCDEF;
	int y = 0x76543210;
	int res = mix_words(x, y);

	printf("%x\n", res);
}
