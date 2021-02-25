#include <iostream>
#include <set>
#include <vector>

using namespace std;

int ans = INT32_MAX;  // 偷懒用 int 最大值表示到达不了的情况，幸好没有花费到达最大值的测试数据

class Air {
 public:
  vector<int> cities;
  int sId = -1, tId = -1; // 用于记录经过城市中目标城市的下标
  int fee;
  Air(int s, int t) { // 通过输入初始化航线
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

    // 如果该航线会从 s 到 t 就更新 ans
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
      set<int> st;  // 用于记录第一条航线的沿途城市
      for (int k = airs[i].sId + 1; k < airs[i].cities.size(); ++k) {
        st.insert(airs[i].cities[k]);
      }

      for (int k = 0; k < airs[j].tId; ++k) {
        if (st.count(airs[j].cities[k])) {  // 如果第二条航线的沿途城市和第一条有重合那么就可以换乘
          ans = min(ans, airs[i].fee + airs[j].fee);
          break;
        }
      }
    }
  }

  if (ans != INT32_MAX) // 偷懒成功
    printf("%d\n", ans);
  else
    printf("-1\n");
}