/* 
 * TODO:
 * 1. 随机化
 * 2. 泛型化
 * 3. 迭代器化
 * 4. 编写异常处理
 */

#include <iostream>
#include <vector>

void quick_sort(std::vector<int> &arr, const int l, const int r) {
  if (l >= r) {
    return;
  }

  const int val = arr[r];
  int i = (int)l - 1;
  for (size_t j = l; j < r; ++j) {
    if (arr[j] <= val) {
      std::swap(arr[++i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[r]);
  quick_sort(arr, l, i);
  quick_sort(arr, i + 2, r);
}

bool sort_check(const std::vector<int> &arr) {
  for (size_t i = 1; i < arr.size(); ++i) {
    if (arr[i] < arr[i - 1]) {
      return false;
    }
  }
  return true;
}

int main(const int argc, const char *argv[]) {
  size_t n;
  std::cin >> n;
  std::vector<int> arr(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  quick_sort(arr, 0, n - 1);

  if (!sort_check(arr)) {
    std::cerr << "Error: quick_sort() not sorted" << std::endl;
    return -1;
  }

  for (size_t i = 0; i < n; ++i) {
    std::cout << arr[i] << std::endl;
  }
}