#include <stdio.h>

/**
 * return 1 if x's bits are all 0 or all 1,
 * or the least significant byte is 0xFF,
 * or the most significant byte is 0x00,
 * otherwise return 0.
 */
int foo(int x) {
  int x_ = ~x;
  int shift_size = (sizeof(int) - 1) << 3;

  int x_lsb = x & 0xFF;
  int x_lsb_ = x ^ 0xFF;

  /**
   * use arithemetic shift to move the most significant byte to the right most,
   * and setting other bit to the most significant bit.
   */
  int x_msb = x >> shift_size;


  return !x_ || !x || !x_lsb || !x_msb;
}

int main() {
  int a = 0xFFFFFFFF;
  int b = 0;
  int c = 0xFF;
  int d = 0x00ABCDEF;
  int e = 0x12345678;

  char ok_msg[] = "ok";
  char fail_msg[] = "is not qualified";

  printf("%08x %s\n", a, foo(a) ? ok_msg : fail_msg);
  printf("%08x %s\n", b, foo(b) ? ok_msg : fail_msg);
  printf("%08x %s\n", c, foo(c) ? ok_msg : fail_msg);
  printf("%08x %s\n", d, foo(d) ? ok_msg : fail_msg);
  printf("%08x %s\n", e, foo(e) ? ok_msg : fail_msg);
}