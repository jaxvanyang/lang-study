#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  int s, t, n;
  scanf("%d%d%d", &s, &t, &n);
  map<int, map<int, int>> graph;  // city -> nexts = [next city -> fee]
  for (int i = 0; i < n; ++i) {
    int fee, cityCnt;
    scanf("%d%d", &fee, &cityCnt);
    vector<int> cities;
    int city;
    for (int j = 0; j < cityCnt; ++j) {
      scanf("%d", &city);
      cities.push_back(city);
    }

    for (int j = 0; j < cityCnt - 1; ++j) {
      for (int k = j + 1; k < cityCnt; ++k) {
        if (graph.count(cities[j]) == 0) {
          graph[cities[j]] = {{cities[k], fee}};
        } else if (graph[cities[j]].count(cities[k]) == 0) {
          graph[cities[j]].insert({cities[k], fee});
        } else if (graph[cities[j]][cities[k]] > fee) {
          graph[cities[j]][cities[k]] = fee;
        }
      }
    }
  }

  int ans = -1;
  if (graph.count(s) && graph[s].count(t)) {
    ans = graph[s][t];
  }
  for (auto &next : graph[s]) {
    int city = next.first;
    int fee = next.second;
    if (graph[city].count(t)) {
      if (ans == -1) {
        ans = fee + graph[city][t];
      } else {
        ans = min(ans, fee + graph[city][t]);
      }
    }
  }

  printf("%d\n", ans);
}