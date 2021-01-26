/* 
 * @from https://vjudge.net/contest/417989#problem/N
 * @analysis 4**k 发一次，1、4、16、64
 * 1、100、10000、1000000
 * 要大于等于 4**k 必须位数要大于 2×（k-1）
 */

#include <iostream>

int main() {
  std::string s;
  std::cin >> s;
  int len = s.length();
  if (len == 0 && s[0] == '0') {
    std::cout << 0 << std::endl;
    return 0;
  }
  int ans = (len + 1) / 2;
  bool flag = true;
  for (int i = 1; i < len; i++) {
    if (s[i] == '1') {
      flag = false;
      break;
    }
  }
  if (flag) {
    --ans;
  }
  std::cout << ans << std::endl;
}