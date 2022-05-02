/*
 * TODO:
 * 1. 随机化
 * 2. 泛型化
 * 3. 迭代器化
 * 4. 编写异常处理
 * 5. 头文件分离
 * 6. 排序最小的 k 个元素
 * 7. 封装到类中
 * 8. 解析命令行参数
 * 9. 可读性优化
 * 10. 参考谷歌风格命名
 */

#include <iostream>
#include <vector>
#include <cassert>

// 使用前必须进行范围判断
template <typename T>
size_t partion(std::vector<T> &arr, const size_t left, const size_t right) {
  // std::cout << "l = " << l << " r = " << r << std::endl;
  const T val = arr[left];
  size_t pivot = right + 1;
  for (size_t i = right; i > left; --i) {
    if (arr[i] >= val) {
      std::swap(arr[--pivot], arr[i]);
    }
  }
  std::swap(arr[left], arr[--pivot]);  // pivot 不会小于 0

  return pivot;
}

template <typename T>
void quick_sort(std::vector<T> &arr, const size_t left, const size_t right) {
  if (left >= right) {
    return;
  }

  const size_t pivot = partion(arr, left, right);
  // 注意不能用减法
  if (left + 1 < pivot) {
    quick_sort(arr, left, pivot - 1);
  }
  quick_sort(arr, pivot + 1, right);
}

bool sort_check(const std::vector<int> &arr) {
  for (size_t i = 1; i < arr.size(); ++i) {
    if (arr[i] < arr[i - 1]) {
      return false;
    }
  }
  return true;
}

// 找出最小的 k 个元素
template <typename T>
void find_k_smallest(std::vector<T> &arr, const size_t left, const size_t right, const size_t k) {
  size_t pivot = partion(arr, left, right);
  size_t cnt = pivot - left;
  if (k <= cnt && 1 < cnt) {
    find_k_smallest(arr, left, pivot - 1, k);
  } else if (cnt + 1 < k) {
    find_k_smallest(arr, pivot + 1, right, k - cnt - 1);
  }

}

bool testK(std::vector<int> &arr, size_t k);

int main(const int argc, const char *argv[]) {
  size_t n;
  std::cin >> n;
  std::vector<int> arr(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  // quick_sort(arr, 0, n - 1);
  // assert(!sort_check(arr));  


  size_t k;
  std::cin >> k;
  find_k_smallest(arr, 0, arr.size() - 1, k);
  for (size_t i = 0; i < n; ++i) {
    std::cout << arr[i] << std::endl;
  }

  assert(testK(arr, k));
}

bool testK(std::vector<int> &arr, size_t k) {
  quick_sort(arr, 0, k);
  const std::vector<int> before(arr.begin(), arr.begin() + k);
  quick_sort(arr, 0, arr.size() - 1);
  const std::vector<int> after(arr.begin(), arr.begin() + k);
  return before == after;
}