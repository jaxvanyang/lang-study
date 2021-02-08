#include <iostream>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int a, b, c;
    cin >> a >> b >> c;
    int ans = min(a, b) * 2;
    if (a > b) {
      a -= b;
      ans += a / 3 * 3;
      a %= 3;
      if (a == 2) {
        ans += 1;
      }
    } else if (a < b) {
      b -= a;
      ans += b / 3 * 6;
      b %= 3;
      if (b == 2) {
        ans += 4;
      }
    }
    cout << ans << endl;
  }
}
/* 
 * 很简单的贪心题，难的是如何证明
 */