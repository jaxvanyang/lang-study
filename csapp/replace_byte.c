#include <stdio.h>

typedef unsigned char *byte_pointer;

unsigned replace_byte(unsigned x, int i, unsigned char b) {
	byte_pointer px = (byte_pointer) &x;
	px[i] = b;
	return x;
}
	
int main() {
	unsigned x = 0x12345678;
	unsigned a = replace_byte(x, 2, 0xab);
	unsigned b = replace_byte(x, 0, 0xab);
	printf("%x\n", a);
	printf("%x\n", b);
}
