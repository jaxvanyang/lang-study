#include <stdio.h>

unsigned shift_and_xor(unsigned x, int size) {
	return (x >> size) ^ x;
}

/* Return 1 if x has odd ones, else 0
	 Assume w = 32	*/
int odd_ones(unsigned x) {
	// after each XOR operation, decrease half bits to indicate odd
	unsigned x_16 = shift_and_xor(x, 1);
	unsigned x_8 = shift_and_xor(x_16, 2);
	unsigned x_4 = shift_and_xor(x_8, 4);
	unsigned x_2 = shift_and_xor(x_4, 8);
	unsigned x_1 = shift_and_xor(x_2, 16);
	return x_1 & 1;
}

int main() {
	const char ODD_MSG[] = "odd\n";
	const char EVEN_MSG[] = "even\n";

	for (unsigned x = 0; x < 10; ++x) {
		const char *msg = odd_ones(x) ? ODD_MSG : EVEN_MSG;
		printf("%08X %s\n", x, msg);
	}
}
