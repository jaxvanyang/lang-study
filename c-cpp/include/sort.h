#pragma once
#include <vector>

// 用于普通数组的插入排序，需要传递数组的大小
template <typename T>
void insertion_sort(T *arr, int size);

template <typename T>
void insertion_sort(std::vector<T> &arr);