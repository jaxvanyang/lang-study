/* 
 * @form https://vjudge.net/contest/417989#problem/K
 */

#include <iostream>

int main() {
  double h, l;
  std::cin >> h >> l;
  printf("%.7lf\n", (l * l - h * h) / 2 / h);
  return 0;
}