#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer begin, int len) {
	for (int i = 0; i < len; ++i) {
		printf("%.2x ", begin[i]);
	}
	puts("");
}

void show_int(int x) {
	show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
	show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
	show_bytes((byte_pointer) &x, sizeof(void *));
}

void show_short(short x) {
	show_bytes((byte_pointer) &x, sizeof(short));
}

void show_long(long x) {
	show_bytes((byte_pointer) &x, sizeof(long));
}

void show_double(double x) {
	show_bytes((byte_pointer) &x, sizeof(double));
}

void test_show_bytes(int val) {
	int ival = val;
	float fval = val;
	int *pval = &ival;
	short sval = val;
	long lval = val;
	double dval = val;

	show_int(ival);
	show_float(fval);
	show_pointer(pval);
	show_short(sval);
	show_long(lval);
	show_double(dval);
}

int main() {
	test_show_bytes(0x12345678);
}
