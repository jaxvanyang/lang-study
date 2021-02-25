#include <deque>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;
  scanf("%d", &n);
  vector<int> nums;
  for (int i = 0; i < n; ++i) {
    int num;
    scanf("%d", &num);
    nums.push_back(num);
  }
  for (int i = 0; i < n; ++i) {
    nums.push_back(nums[i]);
  }
  vector<int> index{0};
  for (int i = 0; i < 2 * n; ++i) {
    index.push_back(index.back() + nums[i]);
  }

  // 存放 [l, r] 中对最小值有贡献的元素
  // queMin.front 始终是 [l, r] 中的最小值，在每次移动时维护这个性质即可
  deque<int> queMin;
  for (int i = 1; i <= n; ++i) {
    // 单调队列需要和队尾比较，因为可能出现新元素不小于队首但小于队尾的情况，这时依然需要更新队列
    while (queMin.size() && queMin.back() > index[i]) queMin.pop_back();
    queMin.push_back(index[i]);
  }
  int l = 1, r = n;
  int ans = 0;
  while (l <= n) {

    // 注意单调队列中存放的是整个扩展数组的前缀和
    if (queMin.front() - index[l - 1] >= 0) ++ans;

    if (index[l] == queMin.front()) queMin.pop_front();
    ++l;
    ++r;
    while (queMin.size() && index[r] < queMin.back()) queMin.pop_back();
    queMin.push_back(index[r]);
  }
  printf("%d\n", ans);
}