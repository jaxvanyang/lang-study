/*
 * @from https://vjudge.net/contest/417990#problem/I
 */

#include <iostream>
#include <set>
#include <vector>

using namespace std;
using ull = unsigned long long;

int main() {
  ull n, w, k;
  cin >> n >> w >> k;
  vector<ull> as, ts, index(1, 0UL);
  for (int i = 0; i < n; ++i) {
    ull a;
    cin >> a;
    as.push_back(a);
    index.push_back(index.back() + a);
  }
  for (int i = 0; i < n; ++i) {
    ull t;
    cin >> t;
    ts.push_back(t);
  }

  ull ans = 0;
  for (int l = 0; l < n; ++l) {
    int r = l;
    ull sum = 0;
    while (r < n && sum + ts[r] <= k) {
      sum += ts[r++];
    }
    set<int> used;
    for (int i = 0; i < w && r < n; ++i) {
      int p = -1;
      ull max = 0;
      for (int j = l; j < r; ++j) {
        if (ts[j] > max && used.count(j) == 0) {
          max = ts[j];
          p = j;
        }
      }
      if (p == -1 && r == n) {
        break;
      }
      if (p == -1) {
        sum += (ts[r++] + 1) / 2;
        used.insert(r);
      }
      if (sum > k) {
        break;
      }
      used.insert(p);
      sum -= max / 2;
      while (r < n && sum + ts[r] <= k) {
        sum += ts[r++];
      }
    }
    ull res = index[r] - index[l];
    ans = std::max(ans, res);
  }
  cout << ans << endl;
  return 0;
}