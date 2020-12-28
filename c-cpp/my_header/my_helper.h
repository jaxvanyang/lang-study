#pragma once
#include <iostream>
#include <vector>

using namespace std;

namespace my_helper {

    template <typename T>
    void printArr(const T *arr, const int &size);

    template <typename T>
    void printArr(const vector<T> &arr);

    // 使用时需要将二维数组转化为指针形式
    template <typename T>
    void printMatrix(T **matrix, const int &rowSize, const int &colSize);   // 给 matrix 加 const 会无法匹配临时变量

    template <typename T>
    void printMatrix(const vector<vector<T>> & matrix);
}  // namespace my_helper
