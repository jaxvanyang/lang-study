#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(const int argc, const char *argv[]) {
  int32_t x = 0x12345678;
  int64_t y = 0x123456789abcdef0;
  printf("x = %" PRId32 ", y = %" PRId64 "\n", x, y);
}