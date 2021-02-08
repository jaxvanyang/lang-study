#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<set<int>> edges(n + 1, set<int>());
  while (m--) {
    int x, y;
    cin >> x >> y;
    edges[x].insert(y);
    edges[y].insert(x);
  }
  // cout << "Hello " << endl;

  set<int> nodes;
  for (int i = 0; i < k; ++k) {
    int c;
    cin >> c;
    nodes.insert(c);
  }

  int first = *nodes.begin();
  auto nexts = edges[first];
  nodes.erase(first);
  while (nexts.size()) {
    // cout << "dead" << endl;
    auto copy = nexts;
    nexts.clear();
    for (auto &u : copy) {
      nodes.erase(u);
      for (auto &v : edges[u]) {
        nexts.insert(v);
      }
      edges[u].clear();
    }
  }
  if (nodes.size()) {
    cout << "NO" << endl;
  } else {
    cout << "YSE" << endl;
  }
}

/*
 * @from http://acm.csust.edu.cn/contest/125/problem/B
 * @analysis 只要在一个连通分量中就可以满足
 */