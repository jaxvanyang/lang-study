/* 
 * @from https://vjudge.net/contest/417989#problem/O
 * @input n, l, r
 * @analysis min =
 */

#include <iostream>
#include <cmath>

int main() {
  int n, l, r;
  std::cin >> n >> l >> r;
  int min = pow(2, l) - 1 + n - l;
  int max = pow(2, r) - 1 + pow(2, r - 1) * (n - r);
  std::cout << min << ' ' << max << std::endl;
}