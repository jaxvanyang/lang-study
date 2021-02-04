/*
 * @from https://vjudge.net/contest/417990#problem/E
 */

#include <iostream>
#include <vector>
using ll = long long;
using namespace std;

inline ll sqr(int x) { return x * (ll)x; }

int main() {
  int n, x1, y1, x2, y2;
  std::cin >> n >> x1 >> y1 >> x2 >> y2;

  vector<pair<ll, ll>> dist;
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    dist.push_back({sqr(x - x1) + sqr(y - y1), sqr(x - x2) + sqr(y - y2)});
  }
  dist.push_back({0UL, 0UL});

  ll ans = 8e18;
  for (const auto &p : dist) {
    ll r1 = p.first;
    ll r2 = 0;
    for (const auto &q : dist) {
      if (q.first > r1) {
        r2 = max(r2, q.second);
      }
    }
    ans = min(ans, r1 + r2);
  }
  cout << ans << endl;
}