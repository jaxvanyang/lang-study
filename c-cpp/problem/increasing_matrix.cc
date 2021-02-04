/* 
 * @from https://vjudge.net/contest/417990#problem/G
 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> matrix(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> matrix[i][j];
    }
  }
  int ans = 0;
  for (int i = n - 1; i >= 0; --i) {
    for (int j = m - 1; j >= 0; --j) {
      int &a = matrix[i][j];
      int b = i == n - 1 ? 1e5 : matrix[i + 1][j];
      int c = j == m - 1 ? 1e5 : matrix[i][j + 1];
      if (a >= b || a >= c) {
        cout << -1 << endl;
        return 0;
      }
      if (a == 0) {
        a = min(b, c) - 1;
      }
      ans += a;
    }
  }
  cout << ans << endl;
}