/* 
 * @from https://vjudge.net/contest/417989#problem/M
 */

#include <iostream>

int main() {
  long long n;
  long long sum = 0;
  std::cin >> n;
  long long max;
  std::cin >> max;
  sum += max;
  for (int i = 1; i < n; i++) {
    long long a;
    std::cin >> a;
    sum += a;
    max = std::max(max, a);
  }
  if (sum % 2 == 0 && max <= sum - max) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  // std::cout << sum << std::endl;
  return 0;
}