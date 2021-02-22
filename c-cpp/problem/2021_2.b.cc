#include <iostream>
#include <vector>

using namespace std;

const int maxn = 1e4 + 5;

class Graph {
 public:
  int v, e;
  vector<vector<vector<int>>> adj;
  Graph(int v) : v(v) {
    e = 0;
    adj = vector<vector<vector<int>>>(v);
  }

  void updateEdge(int p, int q, int fee) {
    int idx = -1;
    for (int i = 0; i < adj[p].size(); ++i) {
      if (adj[p][i][0] == q) {
        idx = i;
        break;
      }
    }
    if (idx == -1) {
      adj[p].push_back({q, fee});
    } else {
      adj[p][idx][1] = min(adj[p][idx][1], fee);
    }
  }

  int getFee(int p, int q) {
    for (int i = 0; i < adj[p].size(); ++i) {
      if (adj[p][i][0] == q) {
        return adj[p][i][1];
      }
    }
    return -1;
  }

  int getAns(int s, int t) {
    int ans = -1;
    for (int i = 0; i < adj[s].size(); ++i) {
      int city = adj[s][i][0];
      int fee = adj[s][i][1];
      for (int j = 0; j < adj[city].size(); ++j) {
        if (adj[city][j][0] == t) {
          if (ans == -1) {
            ans = fee + adj[city][j][1];
          } else {
            ans = min(ans, fee + adj[city][j][1]);
          }
        }
      }
    }
    return ans;
  }
};

int main() {
  int s, t, n;
  scanf("%d%d%d", &s, &t, &n);
  Graph graph = Graph(maxn);

  for (int i = 0; i < n; ++i) {
    int fee, cityCnt;
    scanf("%d%d", &fee, &cityCnt);
    vector<int> cities;
    int city;
    for (int j = 0; j < cityCnt; ++j) {
      scanf("%d", &city);
      cities.push_back(city);
    }

    for (int j = 0; j < cityCnt; ++j) {
      int p = cities[j];
      for (int k = j + 1; k < cityCnt; ++k) {
        int q = cities[k];
        graph.updateEdge(p, q, fee);
      }
    }
  }

  int ans = graph.getFee(s, t);

  if (ans == -1) {
    ans = graph.getAns(s, t);
  } else {
    ans = min(ans, graph.getAns(s, t));
  }

  printf("%d\n", ans);
}