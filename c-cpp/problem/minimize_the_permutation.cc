/*
 * @from https://vjudge.net/contest/417990#problem/C
 */

#include <iostream>

const int maxn = 105;
int nums[maxn];

int main() {
  int q;
  std::cin >> q;
  while (q--) {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
      std::cin >> nums[i];
    }
    int l = 0, r = n - 1;
    while (l < r) {
      int i = l, min = nums[l];
      for (int j = l + 1; j <= r; j++) {
        if (nums[j] < min) {
          i = j;
          min = nums[j];
        }
      }
      if (i == l) {
        ++l;
        continue;
      }

      for (int j = i; j > l; --j) {
        nums[j] = nums[j - 1];
      }
      nums[l] = min;
      l = i;
      // std::cout << nums[0];
      // for (int i = 1; i < n; ++i) {
      //   std::cout << ' ' << nums[i];
      // }
      // std::cout << std::endl;
    }
    std::cout << nums[0];
    for (int i = 1; i < n; ++i) {
      std::cout << ' ' << nums[i];
    }
    std::cout << std::endl;
  }
}