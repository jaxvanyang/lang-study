#include <stdio.h>

// Assume w = 32
int any_odd_one(unsigned x) {
	unsigned mask = 0x55555555;
	return !!(mask & x);
}

int main() {
	const char YES_MSG[] = "yes\n";
	const char NO_MSG[] = "no\n";

	for (unsigned x = 0; x < 10; ++x) {
		int result = any_odd_one(x);
		char *msg = result ? YES_MSG : NO_MSG;
		printf("%u %s\n", x, msg);
	}
}
