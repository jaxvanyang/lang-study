/* 
 * @from https://vjudge.net/contest/417990#problem/A
 */

#include <iostream>

int main() {
  int x;
  std::cin >> x;
  int ans = 0;
  ans += x / 5;
  x %= 5;
  ans += x / 4;
  x %= 4;
  ans += x / 3;
  x %= 3;
  ans += x / 2;
  x %= 2;
  ans += x;
  std::cout << ans << std::endl;
}