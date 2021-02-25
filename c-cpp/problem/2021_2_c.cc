#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class UnionFind {
 public:
  int cnt;
  vector<int> ids;
  UnionFind(int n) {
    cnt = n;
    for (int i = 0; i < n; ++i) {
      ids.push_back(i);
    }
  }

  void un(int p, int q) {
    int pId = find(p), qId = find(q);
    if (pId != qId) {
      ids[pId] = qId;
      --cnt;
    }
  }

  int find(int p) {
    if (p != ids[p]) {
      ids[p] = find(ids[p]);
    }
    return ids[p];
  }

  bool isConnected(int p, int q) { return find(p) == find(q); }
};

int main() {
  int n;
  scanf("%d", &n);

  vector<vector<int>> edges;
  for (int i = 0; i < n; ++i) {
    int cost;
    scanf("%d", &cost);
    edges.push_back({cost, i, n});  // 将建信号塔的花费转化成各点到虚拟出来的超级源点的连接花费
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int cost;
      scanf("%d", &cost);
      if (i < j) edges.push_back({cost, i, j});
    }
  }

  sort(edges.begin(), edges.end());
  // 不能使用集合维护边，因为 Kruskal 算法是针对森林设计的
  // 已经加入的点并不一定会彼此连通，它们可能处于不同的树中
  UnionFind uf(n + 1);  //所以要用并查集
  int ans = 0;
  int i = 0;
  while (uf.cnt > 1) {
    if (!uf.isConnected(edges[i][1], edges[i][2])) {
      ans += edges[i][0];
      uf.un(edges[i][1], edges[i][2]);
    }
    ++i;
  }
  printf("%d\n", ans);
}