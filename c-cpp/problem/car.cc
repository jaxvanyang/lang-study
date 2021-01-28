/* 
 * @from https://vjudge.net/contest/417990#problem/D
 * @note 使用输入输出流会超时
 */

#include <iostream>

const int maxn = 1e5 + 5;
int nums[maxn];

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; ++i) {
    int n;
    scanf("%d", &n);
    for (int j = 1; j <= n; ++j) {
      scanf("%d", nums + j);
    }
    long long ans = 0, time = 1;
    int d = nums[n] - nums[n - 1];
    for (int j = n; j >= 1; --j) {
      int d1 = nums[j] - nums[j - 1];
      time = (d1 * time + d - 1) / d;
      ans += time;
      d = d1;
    }
    printf("Case #%d: %lld\n", i, ans);
  }
}