#include <iostream>
// #include <map>
#include <climits>
#include <vector>

using namespace std;
const int maxn = 1e4 + 5;

int graph[maxn][maxn];

int main() {
  for (int i = 0; i < maxn; ++i) {
    for (int j = 0; j < maxn; ++j) {
      graph[i][j] = INT_MAX;
    }
  }
  int s, t, n;
  scanf("%d%d%d", &s, &t, &n);
  // map<int, map<int, int>> graph;  // city -> nexts = [next city -> fee]
  // vector<vector<int>> graph(maxn, vector<int>(maxn, INT_MAX));

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
        graph[p][q] = min(graph[p][q], fee);
      }
    }
  }

  int ans = graph[s][t];
  // cout << ans << endl;
  for (int i = 0; i < maxn; ++i) {
    if (graph[s][i] != INT_MAX && graph[i][t] != INT_MAX) {
      ans = min(ans, graph[s][i] + graph[i][t]);
    }
  }

  printf("%d\n", ans);
}