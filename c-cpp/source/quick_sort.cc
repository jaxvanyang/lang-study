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
 */

#include <iostream>
#include <vector>

template <typename T>
void quick_sort(std::vector<T> &arr, const size_t l, const size_t r) {
  if (l >= r) {
    return;
  }

  const T val = arr[l];
  size_t i = r + 1;
  for (size_t j = r; j > l; --j) {
    if (arr[j] >= val) {
      std::swap(arr[--i], arr[j]);
    }
  }
  std::swap(arr[l], arr[i - 1]);

  // 使用无符号整型必须对减法特判
  if (i >= 2) {
    quick_sort(arr, l, i - 2);
  }
  quick_sort(arr, i, r);
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

  std::cout << "n = " << n << std::endl;

  if (!sort_check(arr)) {
    std::cerr << "Error: quick_sort() not sorted" << std::endl;
    return -1;
  }

  for (size_t i = 0; i < n; ++i) {
    std::cout << arr[i] << std::endl;
  }
}