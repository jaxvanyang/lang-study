/*
 * @from https://vjudge.net/contest/417990#problem/B
 */

#include <iostream>

int main() {
  int x1, x2, x3, x4, x5, x6;
  while (std::cin >> x1 >> x2 >> x3 >> x4 >> x5 >> x6) {
    if (x1 + x2 + x3 + x4 + x5 + x6 == 0) {
      break;
    }
    int ans = x6 + x5 + x4;
    x1 -= x5 * 11;
    x1 = x1 < 0 ? 0 : x1;
    x2 -= x4 * 5;
    x1 += x2 < 0 ? x2 * 4 : 0;
    x2 = x2 < 0 ? 0 : x2;
    x1 = x1 < 0 ? 0 : x1;
    ans += x3 / 4;
    x3 %= 4;
    if (x3 != 0) {
      ++ans;
      if (x3 == 3) {
        --x2;
        x1 -= 5;
      } else if (x3 == 2) {
        x2 -= 3;
        x1 -= 6;
      } else if (x3 == 1) {
        x2 -= 5;
        x1 -= 7;
      }
      x1 = x1 < 0 ? 0 : x1;
      x2 = x2 < 0 ? 0 : x2;
    }
    ans += x2 / 9;
    x2 %= 9;
    ans += x2 == 0 ? 0 : 1;
    x1 -= 36 - 4 * x2;
    if (x1 > 0) {
      ans += x1 / 36;
      ans += x1 % 36 > 0 ? 1 : 0;
    }
    std::cout << ans << std::endl;
  }
  return 0;
}