// #include <cstring>

#include "linear_algebra.h"

using namespace std;

// 为了方便定义为全局变量
Vector u, v;
Matrix A, B;  // 命名特例，数学中的常用表示方法

int LaunchMenu();
void AddTwoVector();
void ModifyVector(Vector &v);

int main() {
  // 必须使用这两条语句才能混用 wcout 和 cout
  ios::sync_with_stdio(false);
  wcout.imbue(locale(""));
  // TODO: 暂且使用 wcout 输出，后续统一输出方法

  Matrix testM = Matrix(3, 2, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
  Vector testV = Vector(kHorizontal, 3, 0.0, 2.0, 0.0);
  cout << endl;
  if (testM.LinearTransform(testV)) {
    testV.Print();
  }
  return 0;

  wcerr << L"Oh no~" << endl;

  while (true) {
    if (!LaunchMenu()) break;
  }

  return 0;
}

int LaunchMenu() {
  int opt = 0;  // 用于记录选择，是 option 的缩写
  wcout << L"你有两个向量 u 和 v，两个矩阵 A 和 B\n"
           L"请输入数字选择操作：\n"
           "0. 退出\n"
           "1. 打印 u、v、A 和 B\n"
           "2. 修改 u\n"
           "3. 修改 v\n";
  wcin >> opt;
  switch (opt) {
    case 1:
      wcout << L"u:\n";
      u.Print();
      wcout << L"v:\n";
      v.Print();
      wcout << L"A:\n";
      A.Print();
      wcout << L"B:\n";
      B.Print();
      return 1;
    case 2:
      ModifyVector(u);
      return 2;
    case 3:
      ModifyVector(v);
      return 3;
    default:
      return 0;
  }
  return 0;
}

void ModifyVector(Vector &v) {
  int size = 0;
  double *arr = nullptr;
  wcout << L"请输入向量的大小：\n";  // 必须要加 L 标识
  wcin >> size;                      // 使用 cin 会导致不同步
  arr = new double[size];
  wcout << L"请输入第一个向量各分量的大小：\n";
  for (int i = 0; i < size; i++) {
    wcin >> arr[i];
  }
  v = Vector(arr, size);
  delete[] arr;
}

void AddTwoVector() {
  int size = 0;
  double *arr_1 = nullptr, *arr_2 = nullptr;
  wcout << L"请输入向量的大小：\n";  // 必须要加 L 标识
  wcin >> size;                      // 使用 cin 会导致不同步
  arr_1 = new double[size], arr_2 = new double[size];
  wcout << L"请输入第一个向量各分量的大小：\n";
  for (int i = 0; i < size; i++) {
    wcin >> arr_1[i];
  }
  wcout << L"请输入第二个向量各分量的大小：\n";
  for (int i = 0; i < size; i++) {
    wcin >> arr_2[i];
  }
  Vector v_1 = Vector(arr_1, size);
  Vector v_2 = Vector(arr_2, size);
  delete[] arr_1;
  arr_1 = nullptr;
  delete[] arr_2;
  arr_2 = nullptr;
  Vector res = v_1 + v_2;
  res.Print();
}