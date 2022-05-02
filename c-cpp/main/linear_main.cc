#include "linear_algebra.h"

using namespace std;

Vector u = Vector(kVertical, 2, 1.0, 0.0);
Vector v = Vector(kVertical, 2, 0.0, 1.0);
// 为了方便采用了数学中常用的大写命名矩阵
Matrix A = Matrix(2, 2, 1.0, 0.0, 0.0, 1.0);
Matrix B = Matrix(2, 2, -1.0, 0.0, 0.0, -1.0);

inline void Pause(const string &s = "按回车键返回主菜单");
inline int GetSelectio();
int LaunchMenu();

void PrintAll();
void Modify();
void Calculate();

// 修改成功返回 true
bool ModifyVector(Vector &v);
bool ModifyMatrix(Matrix &m);

void AddTwoVector();

int main() {
  while (true) {
    if (!LaunchMenu()) break;
  }
  return 0;
}

inline void Pause(const string &s) {
  cout << endl << s << endl;
  getchar();
}

inline int GetSelection() {
  int selection = 0;
  cin >> selection;
  getchar();  // 吃掉多余的换行，防止换行影响到后面利用 getchar() 暂停
  return selection;
}

int LaunchMenu() {
  cout << "你有两个向量 u 和 v，两个矩阵 A 和 B\n"
          "请输入数字选择操作：\n"
          "0. 退出\n"
          "1. 打印 u、v、A 和 B\n"
          "2. 修改向量或矩阵\n"
          "3. 计算指定的表达式\n";
  switch (GetSelection()) {
    case 1:
      PrintAll();
      return 1;
    case 2:
      Modify();
      return 2;
    case 3:
      Calculate();
      return 3;
    default:
      return 0;
  }
  return 0;
}

void PrintAll() {
  cout << "向量 u：\n";
  u.Print();
  cout << endl;
  cout << "向量 v：\n";
  v.Print();
  cout << endl;
  cout << "矩阵 A：\n";
  A.Print();
  cout << endl;
  cout << "矩阵 B：\n";
  B.Print();
  Pause();
}

void Modify() {
  cout << "请选择要修改的变量：\n"
          "0. 取消修改\n"
          "1. 向量 u\n"
          "2. 向量 v\n"
          "3. 矩阵 A\n"
          "4. 矩阵 B\n";
  switch (GetSelection()) {
    case 1:
      if (ModifyVector(u)) {
        cout << "修改成功！修改后的向量 u：\n";
        u.Print();
      } else {
        cout << "修改失败：（\n";
      }
      break;
    case 2:
      if (ModifyVector(v)) {
        cout << "修改成功！修改后的向量 v：\n";
        v.Print();
      } else {
        cout << "修改失败：（\n";
      }
      break;
    case 3:
      if (ModifyMatrix(A)) {
        cout << "修改成功！修改后的矩阵 A：\n";
        A.Print();
      } else {
        cout << "修改失败：（\n";
      }
      break;
    case 4:
      if (ModifyMatrix(B)) {
        cout << "修改成功！修改后的矩阵 B：\n";
        B.Print();
      } else {
        cout << "修改失败：（\n";
      }
      break;
    default:
      break;
  }
  getchar();
  Pause();
}

void Calculate() {}

bool ModifyVector(Vector &v) {
  // TODO: use try-catch to verify
  auto orientation = kVertical;
  int size = 0;
  double *values = nullptr;

  cout << "请输入向量的方向：\n"
          "0. 纵向\n"
          "1. 横向\n";
  if (GetSelection() == 1) {
    orientation = kHorizontal;
  }
  cout << "请输入向量的大小：\n";
  cin >> size;
  values = new double[size];
  cout << "请输入向量各分量的大小：\n";
  for (int i = 0; i < size; i++) {
    cin >> values[i];
  }
  v = Vector(values, size, orientation);
  delete[] values;
  return true;
}

bool ModifyMatrix(Matrix &m) {
  int row_size = 0, col_size = 0;
  double *values = nullptr;

  cout << "请输入矩阵的行数：\n";
  cin >> row_size;
  cout << "请输入矩阵的列数：\n";
  cin >> col_size;
  values = new double[row_size * col_size];
  for (int i = 0; i < row_size; i++) {
    cout << "请输入第 " << i + 1 << " 行的元素：\n";
    for (int j = 0; j < col_size; j++) {
      cin >> values[i * col_size + j];
    }
  }
  m.row_size_ = row_size;
  m.col_size_ = col_size;
  delete[] m.values_;
  m.values_ = values;
  
  return true;
}

void AddTwoVector() {
  int size = 0;
  double *arr_1 = nullptr, *arr_2 = nullptr;
  cout << "请输入向量的大小：\n";  // 必须要加 L 标识
  cin >> size;                     // 使用 cin 会导致不同步
  arr_1 = new double[size], arr_2 = new double[size];
  cout << "请输入第一个向量各分量的大小：\n";
  for (int i = 0; i < size; i++) {
    cin >> arr_1[i];
  }
  cout << "请输入第二个向量各分量的大小：\n";
  for (int i = 0; i < size; i++) {
    cin >> arr_2[i];
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