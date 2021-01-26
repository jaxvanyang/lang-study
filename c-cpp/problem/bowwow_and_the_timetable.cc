/* 
 * @from https://vjudge.net/contest/417989#problem/N
 * @analysis 4**k 发一次，1、4、16、64
 * 1、100、10000、1000000
 * 要大于等于 4**k 必须位数要大于 2×（k-1）
 * 1. 双位，答案就是 len / 2
 * 2. 单位，只有一个 1 就是 len / 2；有多个就加 1
 */

#include <iostream>

int main() {
  std::string s;
  std::cin >> s;
  int len = s.length();
  int ans = len / 2;
  if (len % 2 == 1) {
    for (int i = 1; i < len; i++) {
      if (s[i] == '1') {
        ++ans;
        break;
      }
    }
  }
  std::cout << ans << std::endl;
}