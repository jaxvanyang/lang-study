#include <stdio.h>

// Assume w = 32
int any_odd_one(unsigned x) {
	unsigned mask = 0xAAAAAAAA;
	return !!(x & mask);
}

int main() {
	const char YES_MSG[] = "odd\n";
	const char NO_MSG[] = "even\n";

	for (unsigned x = 0; x < 10; ++x) {
		int result = any_odd_one(x);
		const char *msg = result ? YES_MSG : NO_MSG;
		printf("%X %s\n", x, msg);
	}
}
