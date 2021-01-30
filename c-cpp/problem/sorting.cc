/*
 * @from https://vjudge.net/contest/417990#problem/H
 * @analysis
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ull = unsigned long long;

struct Node {
  ull a, b;
  int id;
};

bool cmp(const Node &a, const Node &b) {
  if (a.a * b.b == a.b * b.a) {
    return a.id < b.id;
  }
  return a.a * b.b > a.b * b.a;
}

int main() {
  int n;
  while (cin >> n) {
    vector<Node> nums;
    for (int i = 1; i <= n; ++i) {
      ull a, b, c;
      cin >> a >> b >> c;
      nums.push_back({c, a + b + c, i});
    }
    sort(nums.begin(), nums.end(), cmp);
    cout << nums[0].id;
    for (int i = 1; i < n; ++i) {
      cout << ' ' << nums[i].id;
    }
    cout << endl;
  }
}