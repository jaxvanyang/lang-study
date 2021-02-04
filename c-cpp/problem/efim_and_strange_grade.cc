/*
 * @from https://vjudge.net/contest/417990#problem/F
 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, t;
  cin >> n >> t;
  string s;
  cin >> s;
  vector<int> dp(n + 1, 1e9 + 1);
  int l = 0;
  while (l < n && s[l] != '.') {
    ++l;
  }
  for (int i = n - 1; i > l; --i) {
    if (s[i] > '4') {
      dp[i] = 1;
    } else if (s[i] == '4') {
      dp[i] = 1 + dp[i + 1];
    } else {
      dp[i] = 1e9 + 1;
    }
  }

  int pos = n;
  for (int i = n - 1; i > l; --i) {
    if (dp[i] <= t) {
      pos = i;
    }
  }
  if (pos == n) {
    cout << s << endl;
    return 0;
  }
  s.resize(pos);
  // cout << pos << endl;

  int add = 1;
  for (int i = pos - 1; i > l; --i) {
    char tmp = '0' + (s[i] + add - '0') % 10;
    add = s[i] + add > '9' ? 1 : 0;
    s[i] = tmp;
    if (!add) {
      break;
    }
  }
  if (add == 1) {
    for (int i = l - 1; i >= 0; --i) {
      char tmp = '0' + (s[i] + add - '0') % 10;
      add = s[i] + add > '9' ? 1 : 0;
      s[i] = tmp;
      if (!add) {
        break;
      }
    }
  }
  if (add) {
    s.insert(s.begin(), '1');
  }
  pos = s.length();
  while (pos - 1 > l + add && s[pos - 1] == '0') {
    --pos;
  }
  if (s[pos - 1] == '.') {
    --pos;
  }
  s.resize(pos);
  cout << s << endl;
}