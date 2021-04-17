#include <iostream>
using namespace std;

int *buildNext(const string &p);

// 如果没找到则返回 -1
int match(const string &s, const string &p);

// 接收两个命令行参数，分别表示字符串和模式串，如果没有命令行参数就使用标准输入
int main(const int argc, const char *argv[]) {
  // cout << argc << endl;
  string s, p;
  if (argc == 3) {
    s = argv[1], p = argv[2];
  } else {
    cin >> s >> p;
  }
  int idx = match(s, p);
  if (idx == -1) {
    cout << "there is no " << p << " in " << s << endl;
  } else {
    cout << "found " << p << " in " << s << " at " << idx << endl;
  }
}

int *buildNext(const string &p) {
  int n = p.length();
  if (n == 0) {
    return nullptr;
  }
  int *next = new int[n];
  int l = next[0] = -1, r = 0;
  while (r < n - 1) {
    if (l < 0 || p[l] == p[r]) {
      ++l, ++r;
      next[r] = l;
    } else {
      l = next[l];
    }
  }
  return next;
}

int match(const string &s, const string &p) {
  const int sLen = s.length(), pLen = p.length();
  int i = 0, j = 0;
  int *next = buildNext(p);
  while (i < sLen && j < pLen) {
    cout << "i = " << i << " j = " << j << endl;
    if (j < 0 || s[i] == p[j]) {
      ++i, ++j;
    } else {
      j = next[j];
    }
  }
  delete[] next;
  return i - j >= sLen ? -1 : i - j;
}