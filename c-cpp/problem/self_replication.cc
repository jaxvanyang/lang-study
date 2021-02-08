#include <iostream>

using namespace std;

int main() {
  string s;
  cin >> s;
  int len = s.length();
  if (len <= 1) {
    cout << 0 << endl;
    return 0;
  }
  int half = len / 2;
  if (len % 2) {
    for (int i = 0; i < half; ++i) {
      cout << 9;
    }
  } else {
    bool left_is_bigger = false;
    for (int l = 0, r = half; l < half; ++l, ++r) {
      if (s[l] != s[r]) {
        if (s[l] > s[r]) {
          left_is_bigger = true;
        }
        break;
      }
    }

    if (left_is_bigger) {
      long long num = 0;
      for (int i = 0; i < half; ++i) {
        num = num * 10 + s[i] - '0';
      }
      cout << num - 1;
    } else {
      cout << s.substr(0, half);
    }
  }

  putchar('\n');
  return 0;
}