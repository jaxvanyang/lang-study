/*
 * @from https://vjudge.net/contest/417989#problem/L
 */

#include <iostream>

const int maxn = 1e3 + 5;
int ansCnt[maxn][5];

int main() {
  int n, m;
  long long ans = 0;
  std::cin >> n >> m;
  for (int i = 0; i < n; i++) {
    std::string s;
    std::cin >> s;
    for (int j = 0; j < s.length(); ++j) {
      ansCnt[j][s[j] - 'A']++;
    }
  }
  for (int i = 0; i < m; i++) {
    int s;
    std::cin >> s;
    int maxV = ansCnt[i][0];
    for (int j = 1; j < 5; j++) {
      maxV = std::max(maxV, ansCnt[i][j]);
    }
    ans += s * maxV;
  }
  std::cout << ans << std::endl;
}