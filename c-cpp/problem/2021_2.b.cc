#include <iostream>
#include <set>
#include <vector>

using namespace std;

int ans = INT32_MAX;

class Air {
 public:
  vector<int> cities;
  int sId = -1, tId = -1;
  int fee;
  Air(int s, int t) {
    int cityCnt;
    scanf("%d%d", &fee, &cityCnt);
    int city;
    for (int j = 0; j < cityCnt; ++j) {
      scanf("%d", &city);
      if (city == s) {
        sId = j;
      } else if (city == t) {
        tId = j;
      }
      cities.push_back(city);
    }
    if (sId != -1 && tId != -1 && sId < tId) {
      ans = min(ans, fee);
    }
  }
};

int main() {
  int s, t, n;
  scanf("%d%d%d", &s, &t, &n);
  vector<Air> airs;
  for (int i = 0; i < n; ++i) {
    airs.push_back(Air(s, t));
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }
      if (airs[i].sId == -1 || airs[j].tId == -1) {
        continue;
      }
      set<int> st;
      for (int k = airs[i].sId + 1; k < airs[i].cities.size(); ++k) {
        st.insert(airs[i].cities[k]);
      }

      for (int k = 0; k < airs[j].tId; ++k) {
        if (st.count(airs[j].cities[k])) {
          ans = min(ans, airs[i].fee + airs[j].fee);
          break;
        }
      }
    }
  }
  if (ans != INT32_MAX)
    printf("%d\n", ans);
  else
    printf("-1\n");
}