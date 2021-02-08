#include <iostream>
using namespace std;

int main() {
  bool isGoods[128]{};
  string s;
  cin >> s;
  int i = 0;
  while (i < s.length()) {
    bool isOdd = true;
    while (i + 1 < s.length() && s[i + 1] == s[i]) {
      ++i;
      isOdd = !isOdd;
    }
    if (isOdd) {
      isGoods[s[i]] = true;
    }
    ++i;
  }
  int ans = 26;
  for (int i = 'a'; i <= 'z'; ++i) {
    if (isGoods[i]) {
      --ans;
    }
  }
  cout << ans << endl;
}