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
  vector<vector<ll>> rules;
  vector<ll> dp(n + 1);
  for (ll i = 0; i < n; ++i) {
    ll s, p;
    scanf("%lld%lld", &s, &p);
    rules.push_back({s, p});
  }

  dp[n] = INT64_MAX;
  for (int i = n - 1; i >= 0; --i) {
    dp[i] = min(dp[i + 1], rules[i][0] * rules[i][1]);
  }
  // for (int i = 0; i < n; ++i) {
  //   cout << dp[i] << endl;
  // }

  while (q--) {
    ll num;
    scanf("%lld", &num);
    // cout << find(rules, num) << endl;
    int id = find(rules, num);
    ll ans = rules[id][1] * num;
    // cout << "id = " << id << " ans = " << ans << endl;
    ans = min(ans, dp[id + 1]);
    printf("%lld\n", ans);
  }
}