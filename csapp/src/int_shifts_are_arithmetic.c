#include <stdio.h>

int int_shifts_are_arithmetic() {
  int shift_size = (sizeof(int) << 3) - 1;
  int x = 0x8FFFFFFF;
  int y = 0xFFFFFFFF;
  return x >> shift_size == y;
}

int main() {
  char yes_msg[] = "int shifts are arithmetic\n";
  char no_msg[] = "int shifts are logical\n";
  int result = int_shifts_are_arithmetic();
  puts(result ? yes_msg : no_msg);

  return result;
}
