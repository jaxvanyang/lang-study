#include <stdio.h>

typedef unsigned char *byte_pointer;

int is_little_endian() {
	int x = 1;
	byte_pointer px = (byte_pointer) &x;
	unsigned char ch = 1;
	return px[0] == ch;
}
	

int main() {
	int res = is_little_endian();
	printf("This is a %s endian machine\n", res ? "little" : "big");
	
	// return 0 to indicate little endian, 1 to indicate big endian
	return !res;
}
