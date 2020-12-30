#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#define SIZE_OF_ARR(ARR) (sizeof(ARR) / sizeof(ARR[0]))

using namespace std;

template <typename T>
void printArr(const T *arr, const int &size);

template <typename T>
void printArr(const vector<T> &arr);

// 使用时需要将二维数组转化为指针形式
// 给 matrix 加 const 会无法匹配临时变量
template <typename T>
void printMatrix(T **matrix, const int &rowSize, const int &colSize);

template <typename T>
void printMatrix(const vector<vector<T>> &matrix);

// TODO: 改写成内联函数
bool isDigit(char ch);

int strToInt(char *str);
double strToDouble(char *str);

int writeInputToFile(char *fileName);
int writeInput();