#pragma once

#include <cstdarg>
#include <cstring>
#include <iostream>
#include <vector>

enum Orientation { kVertical, kHorizontal };  // 用于指示向量的方向

/* 向量类
 *
 * 向量的大小在初始化后就不应该改变，只能改变分量和方向
 * 数据成员包括：orientation_ size_ values_
 * 应特别注意对指针变量 values_ 的操作
 */
class Vector {
 public:
  // 向量构造函数
  // 需先指定大小，默认为 0;再指定方向，方向默认为垂直;
  // 最后是各分量的大小,必须是,double 类型
  Vector(const Orientation orientation = kVertical, const int size = 0, ...);
  // 构造函数初始化时，对象内部的数据还不确定，不能直接进行释放内存的操作
  Vector(const Vector &v);

  // 从确定长度的数组构造向量
  template <typename T>
  Vector(const T *arr, const int size = 0,
         const Orientation orientation = kVertical);

  Vector operator=(const Vector &v);

  // 向量析构函数
  // 因为只需要释放分量的内存，工作比较少，可以用内联实现
  inline ~Vector();

  /*  Vector friends **********************************/
  friend class Matrix;
  friend Vector operator*(const int k, const Vector &v);

  inline int get_size();
  inline Orientation get_orientation();
  // 改变向量的方向，并返回改变后的方向
  inline Orientation change_orientation();
  // 返回用容器 vector 承载的拷贝
  std::vector<double> get_vector_copy();

  // 返回指定的分量，序号从 0 开始，可直接对分量进行修改
  inline double &operator[](const int i);

  // TODO: 获取垂直方向的向量
  // 通过调用构造函数实现，指定向量方向为垂直
  // static Vector get_vectical_vector(const int size, ...);

  Vector Copy();
  void Print();

  // TODO: 向量运算待测试
  /* 向量加减 */
  // 加上一个向量，在自身上修改
  Vector &operator+=(const Vector &v);
  // 返回两个向量的和向量，两者必须长度相同
  Vector operator+(const Vector &v);
  Vector &operator-=(const Vector &v);
  Vector operator-(const Vector &v);

  /* 向量乘除 */
  // 线性乘
  Vector &operator*=(const double k);
  Vector operator*(const double k);
  // 线性除
  Vector &operator/=(const double k);
  Vector operator/(const double k);

  // 数量积（点积）
  double ScalarProductWith(const Vector &v);
  double Dot(const Vector &v);                // 依靠调用 ScalarProductWith() 实现
  // 向量积（叉积）暂时只支持三维向量
  Vector VectorProductWith(const Vector &v);
  Vector Cross(const Vector &v);              // 依靠调用 VectorProductWith() 实现
  Vector operator*(const Vector &v);          // 同上

  // 原地转置向量，并返回转置后的向量
  inline Vector &Transpose();

 protected:
  // 复刻另一个向量，在自身上修改
  inline void fork(const Vector &v);

 private:
  int size_;
  double *values_;
  Orientation orientation_;
};

/* 矩阵类
 * 使用 double *values 存储数据
 * 用 values[i * col_size_ + j] 模拟二维数组 values[i][j] 访问
 * 注意 i 乘的是 col_size_ 而不是 row_size_
 */
class Matrix {
 public:
  // 使用缺省参数来初始化，所以初始化时需要特别小心
  Matrix(const int row_size = 0, const int col_size = 0, ...);
  Matrix(const Matrix &m);

  // 通过调用 Copy() 进行深拷贝
  Matrix operator=(const Matrix &m);

  ~Matrix();

  /*  friends ********************************/
  friend Matrix operator*(const int k, const Matrix &m);
  friend Vector operator*(Vector v, Matrix m);
  friend Vector operator*(Matrix m, Vector v);

  /*  getter and setter **********************/
  // 获得用容器 vector 承载的行向量的副本
  std::vector<double> get_row_vector_copy(const int i);
  // 获得用容器 vector 承载的行向量的副本，不能修改原值
  std::vector<double> get_col_vector_copy(const int i);
  // 获取的是元素的引用，可以修改原值
  inline double &get_item(const int row, const int col);

  // 将行向量的值封装到 Vector 中实现安全访问
  // 可能造成内存泄漏，应尽量少用
  inline Vector &operator[](const int row);

  /*  helper  ********************************/
  Matrix Copy();
  void Print();

  // TODO: 矩阵运算待测试
  /*  重载函数  *******************************/
  Matrix &operator+=(const Matrix &m);
  Matrix operator+(const Matrix &m);
  Matrix &operator-=(const Matrix &m);
  Matrix operator-(const Matrix &m);

  // 线性乘除
  Matrix &operator*=(const int k);
  Matrix operator*(const int k);
  Matrix &operator/=(const int k);
  Matrix operator/(const int k);

  /*  矩阵运算  *******************************/
  // 在向量参数上进行矩阵所表示的线性变换，成功返回 true
  // 因为 class Matrix 在 class Vector 后声明，所以在 Vector 的方法不能使用 Matrix
  // 所以把线性变换放在 Matrix 中
  // 由于要修改参数 v，所以不用 const 修饰
  bool LinearTransform(Vector &v);

  /*  矩阵操作  *******************************/
  Matrix &Transpose();

 protected:
  // 获取行向量开头的指针，可能会有越界问题，只能在类内部使用
  inline double *get_row(const int i);

 private:
  // 为数据成源声明的地方赋值并没有什么意义，因为变量分配的内存空间并不会因此而修改
  int row_size_ = 0, col_size_ = 0;
  double *values_ = nullptr;
};

// TODO: 添加方阵继承矩阵，并编写行列式函数

/*  Vector functions  ********************************************************/

inline Vector::~Vector() { delete[] values_; }

inline int Vector::get_size() { return size_; }

inline Orientation Vector::get_orientation() { return orientation_; }

inline Orientation Vector::change_orientation() {
  return orientation_ = (orientation_ == kHorizontal) ? kVertical : kHorizontal;
}

inline double &Vector::operator[](const int i) {
  if (0 <= i && i < size_) {
    return values_[i];
  }
  std::cerr
      << "错误：索引不在数据范围内\n位置：Vector::operator[](const int i)\n";
  exit(1);
}

inline Vector &Vector::Transpose() {
  this->change_orientation();
  return *this;
}

// 在复刻的同时还回收了之前的存储空间
// 使用内联方式，但是调用了一些函数，可能会对性能有影响
// TODO: 影响待考
void Vector::fork(const Vector &v) {
  orientation_ = v.orientation_;
  size_ = v.size_;
  delete[] values_;
  values_ = new double[size_];
  memcpy(values_, v.values_, size_ * sizeof(double));
}

inline double *Matrix::get_row(const int i) {
  if (0 <= i && i < row_size_) {
    return values_ + i * col_size_;
  }
  std::cerr << "错误：索引不在数据范围内\n位置：Matrix::get_row(const int i)\n";
  exit(1);
}

inline double &Matrix::get_item(const int row, const int col) {
  return values_[row * col_size_ + col];
}

inline Vector &Matrix::operator[](const int row) {
  if (row < 0 || row >= row_size_) {
    std::cerr << "错误：索引不在数据范围内\n"
              << "位置：Matrix::operator[](const int row)\n"
              << "row_size_ = " << row_size_ << std::endl
              << "row = " << row << std::endl;
    exit(1);
  }
  static Vector ret(kHorizontal,
                    0);  // 使用静态变量作为返回值，可能造成内存泄漏
  ret.size_ = col_size_;
  ret.values_ = get_row(row);
  return ret;
}

/*  Linear operation reload functions
 *  让运算不仅可以由类发起
 */

Vector operator*(const int k, const Vector &v);

Matrix operator*(const int k, const Matrix &m);