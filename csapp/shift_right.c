#include <stdio.h>

// Perform a logical right shift using an arithemetic right shift.
unsigned srl(unsigned x, int k) {
  unsigned xsra = (int) x >> k;
  int shift_size = (sizeof(unsigned) << 3) - k;
  unsigned mask = (1 << shift_size) - 1;
  return xsra & mask;
}

// Perform an arithemetic right shift using a logical right shift.
unsigned sra(int x, int k) {
  int xsrl = (unsigned) x >> k;

  // Use unsigned subtraction and NOT operation to fill left end with sign bit
  int shift_size = (sizeof(int) << 3) - k;
  unsigned mask = ((1 << k) - 1) << shift_size;
  unsigned sub_val = 1 << (shift_size - 1);
  unsigned left_end = ~((unsigned) xsrl - sub_val) & mask;
  return xsrl | left_end;
}

int main() {
  char ok_msg[] = "OK\n";
  char err_msg[] = "ERROR\n";

  int k = sizeof(unsigned) << 2;

  unsigned a = 0x01234567;
  unsigned b = 0x89ABCDEF;
  int is_logical_ok = srl(a, k) == a >> k && srl(b, k) == b >> k;
  printf("shift right logically: %s\n", is_logical_ok ? ok_msg : err_msg);

  int c = 0x01234567;
  int d = 0x89ABCDEF;
  int is_arithemetic_ok = sra(c, k) == c >> k && sra(d, k) == d >> k;
  printf("shift right airhemetically: %s\n", is_arithemetic_ok ? ok_msg : err_msg);
}