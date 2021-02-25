#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

int find(vector<vector<ll>> &rules, ll num) {
  int l = 0, r = rules.size();
  while (l < r) {
    int mid = l + (r - l) / 2;
    if (rules[mid][0] > num) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return l - 1;
}

int main() {
  ll n, q;
  scanf("%lld%lld", &n, &q);

  // 使用一个二维数组记录规则，因为题目给出的规则已经有序，所以不需要排序
  vector<vector<ll>> rules;
  for (ll i = 0; i < n; ++i) {
    ll s, p;
    scanf("%lld%lld", &s, &p);
    rules.push_back({s, p});
  }

  // dp[i] 表示 rules[i] 到 rules[n] 中最小的规则花费
  vector<ll> dp(n + 1);
  dp[n] = INT64_MAX;  // 将边界值设置为 long long 的最大值，可以减少边界判断
  for (int i = n - 1; i >= 0; --i) {
    dp[i] = min(dp[i + 1], rules[i][0] * rules[i][1]);  // 因为最小值具有传递性，所以可以用动态规划来做
  }

  // 处理每次查询
  while (q--) {
    ll num;
    scanf("%lld", &num);
    int id = find(rules, num);  // 二分查找到不少于鞭炮数量 num 的规则的下标 id，查找函数定义在 main 函数上面
    ll ans = rules[id][1] * num;
    ans = min(ans, dp[id + 1]);
    printf("%lld\n", ans);
  }
}