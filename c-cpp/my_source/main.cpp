#include "main.h"
#include "my_helper.cpp"
#include "my_helper.h"
#include "my_sort.cpp"
#include "my_sort.h"

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    int arr1[] = {5, 4, 3, 2, 1};
    vector<double> arr2 = {9.5, 9.4, 9.3, 5.1, 2.1};

    // 试验帮助函数
    my_helper::printArr(arr1, SIZE_OF_ARR(arr1));  // 宏不需要命名空间
    my_helper::printArr(arr2);

    // 试验插入排序
    my_sort::insertion_sort(arr1, SIZE_OF_ARR(arr1));
    my_sort::insertion_sort(arr2);

    my_helper::printArr(arr1, SIZE_OF_ARR(arr1));
    my_helper::printArr(arr2);

    // 二维数组必须声明列数
    int matrix1[][3] = {
        {1, 2, 3},
        {4, 5, 6},
    };
    vector<vector<long>> matrix2 = {
        {9, 8},
        {7, 6},
        {5, 4},
    };

    my_helper::printMatrix((int **)matrix1, 2, 3);
    my_helper::printMatrix(matrix2);
}