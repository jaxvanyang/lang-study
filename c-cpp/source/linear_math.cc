#include <cstdarg>
#include <iostream>
#include <vector>

// #include "linear.h"
#include "linear_math.h"

// 由于变长参数列表的解析需要指定变量类型
// 所以在初始化时传入的分量大小必须是 double 类型
Vector::Vector(const Orientation orientation = kVertical, const int size = 0,
               ...) {
  size_ = size;
  orientation_ = orientation;
  values_ = new double[size];

  std::va_list args;
  va_start(args, size);
  for (int i = 0; i < size; i++) { values_[i] = va_arg(args, double); }
  va_end(args);
}

Vector::Vector(const Vector &v) {
  size_ = v.size_;
  orientation_ = v.orientation_;
  values_ = new double[size_];
  memcpy(values_, v.values_, size_ * sizeof(double));
}

// 因为调用了方法，所以参数不能用 const 修饰
Vector Vector::operator=(Vector &v) { return v.Copy(); }

Vector Vector::Copy() {
  Vector copy(orientation_, 0);
  copy.values_ = new double[size_];
  for (int i = 0; i < size_; i++) { copy.values_[i] = values_[i]; }
  return copy;
}

void Vector::Print() {
  if (orientation_ == kVertical) {
    for (int i = 0; i < size_; i++) { std::cout << values_[i] << std::endl; }
  } else {
    std::cout << values_[0];
    for (int i = 1; i < size_; i++) { std::cout << ' ' << values_[i]; }
    std::cout << std::endl;
  }
}

std::vector<double> Vector::get_vector_copy() {
  std::vector<double> copy(size_, 0.0);
  for (int i = 0; i < size_; i++) { copy[i] = values_[i]; }
  return copy;
}


Vector &Vector::operator+=(const Vector &v) {
  if (size_ != v.size_) {
    std::cerr << "错误：变量的长度不相等\n位置：Vector::operator+=(const "
                 "Vector &v)\n";
    exit(1);
  }
  for (int i = 0; i < size_; i++) { values_[i] += v.values_[i]; }
  return *this;
}

// 调用了 += 重载，并且有自己的参数检查，方便定位错误
Vector Vector::operator+(const Vector &v) {
  if (size_ != v.size_) {
    std::cerr
        << "错误：变量的长度不相等\n位置：Vector::operator+(const Vector &v)\n";
    exit(1);
  }
  Vector result = *this;
  result += v;
  return result;
}

Vector &Vector::operator-=(const Vector &v) {
  if (size_ != v.size_) {
    std::cerr << "错误：变量的长度不相等\n位置：Vector::operator-=(const "
                 "Vector &v)\n";
    exit(1);
  }
  for (int i = 0; i < size_; i++) { values_[i] -= v.values_[i]; }
  return *this;
}

// 调用了 -= 重载，并且有自己的参数检查，方便定位错误
Vector Vector::operator-(const Vector &v) {
  if (size_ != v.size_) {
    std::cerr
        << "错误：变量的长度不相等\n位置：Vector::operator-(const Vector &v)\n";
    exit(1);
  }
  Vector result = *this;
  result -= v;
  return result;
}

Vector &Vector::operator*=(const double k) {
  for (int i = 0; i < size_; i++) { values_[i] *= k; }
  return *this;
}

Vector Vector::operator*(const double k) {
  Vector result = *this;
  result *= k;
  return result;
}

Vector &Vector::operator/=(const double k) {
  if (k == 0.0) {
    std::cerr << "错误：除以 0\n位置：Vector::operator/=(const double k)\n";
    exit(1);
  }
  for (int i = 0; i < size_; i++) { values_[i] /= k; }
  return *this;
}

Vector Vector::operator/(const double k) {
  if (k == 0.0) {
    std::cerr << "错误：除以 0\n位置：Vector::operator/(const double k)\n";
    exit(1);
  }
  Vector result = *this;
  result /= k;
  return result;
}

double Vector::ScalarProductWith(const Vector &v) {
  if (size_ != v.size_) {
    std::cerr << "错误：向量大小不相等\n位置：Vector::ScalarProductWith(const "
                 "Vector &v)\n";
    exit(1);
  }
  if (orientation_ != v.orientation_) {
    std::cerr << "错误：向量方向不同\n位置：Vector::ScalarProductWith(const "
                 "Vector &v)\n";
    exit(1);
  }
  double result = 0.0;
  for (int i = 0; i < size_; i++) { result += values_[i] * v.values_[i]; }
  return result;
}
double Vector::Dot(const Vector &v) { return this->ScalarProductWith(v); }

Vector Vector::VectorProductWith(const Vector &v) {
  if (size_ != v.size_) {
    std::cerr << "错误：向量大小不相等\n位置：Vector::VectorProductWith(const "
                 "Vector &v)\n";
    exit(1);
  }
  // TODO: add other dimension defination
  if (size_ != 3) { exit(1); }
  if (orientation_ != v.orientation_) {
    std::cerr << "错误：向量方向不同\n位置：Vector::ScalarProductWith(const "
                 "Vector &v)\n";
    exit(1);
  }
  Vector result = Vector(orientation_);
  result.values_ = new double[3];
  result.size_ = 3;
  for (int i = 0; i < 3; i++) {
    int j = (i + 1) % 3;
    int k = (j + 1) % 3;
    result[i] = values_[j] * v.values_[k] - values_[k] * v.values_[j];
  }
  return result;
}
Vector Vector::Cross(const Vector &v) { return this->VectorProductWith(v); }
Vector Vector::operator*(const Vector &v) { return this->VectorProductWith(v); }

/*  Matrix structor and destructor  ************************************/
Matrix::Matrix(const int row_size = 0, const int col_size = 0, ...) {
  row_size_ = row_size;
  col_size_ = col_size;
  values_ = new double[row_size * col_size];

  std::va_list args;
  // TODO: 修复不是最后参数的编译警告
  va_start(args, row_size * col_size);
  for (int i = 0; i < row_size; i++) {
    for (int j = 0; j < col_size; j++) {
      values_[i * col_size + j] = va_arg(args, double);
    }
  }
  va_end(args);
}

Matrix::Matrix(const Matrix &m) {
  row_size_ = m.row_size_;
  col_size_ = m.col_size_;
  const int size = row_size_ * col_size_;
  values_ = new double[size];
  for (int i = 0; i < size; i++) { values_[i] = m.values_[i]; }
}

Matrix Matrix::operator=(const Matrix &m) { return this->Copy(); }

Matrix::~Matrix() { delete[] values_; }

/*  Matrix getter and setter  ****************************/
std::vector<double> Matrix::get_row_vector_copy(const int i) {
  if (0 <= i && i < row_size_) {
    double *row = get_row(i);
    std::vector<double> ret(col_size_, 0.0);
    for (int j = 0; j < col_size_; j++) { ret[j] = row[j]; }
    return ret;
  }
  std::cerr << "错误：索引不在数据范围内\n位置：Matrix::get_row(const int i)\n";
  exit(1);
}

std::vector<double> Matrix::get_col_vector_copy(const int i) {
  if (0 <= i && i < col_size_) {
    std::vector<double> ret(row_size_, 0.0);
    for (int j = 0; j < row_size_; j++) { ret[j] = values_[j * col_size_ + i]; }
    return ret;
  }
  std::cerr << "错误：索引不在数据范围内\n位置：Matrix::get_col(const int i)\n";
  exit(1);
}

/*  Matrix helper *****************************************/
Matrix Matrix::Copy() {
  Matrix copy = Matrix(0, 0);
  copy.row_size_ = row_size_;
  copy.col_size_ = col_size_;
  copy.values_ = new double[row_size_ * col_size_];
  int size = row_size_ * col_size_;  // 防止重复运算
  for (int i = 0; i < size; i++) {
    copy.values_[i] = values_[i];  // TODO: 可以通过操作内存的函数优化
  }
  return copy;
}

void Matrix::Print() {
  for (int i = 0; i < row_size_; i++) {
    std::cout << values_[i * col_size_];
    for (int j = 1; j < col_size_; j++) {
      std::cout << ' ' << values_[i * col_size_ + j];
    }
    std::cout << std::endl;
  }
}

/*  Matrix 重载函数 ***************************************/
Matrix &Matrix::operator+=(const Matrix &m) {
  if (row_size_ != m.row_size_ || col_size_ != m.col_size_) {
    std::cerr << "错误：矩阵大小不相等\n"
              << "位置：&Matrix::operator+=(const Matrix &m)\n"
              << "row_size_ = " << row_size_ << " col_size_ = " << col_size_
              << std::endl
              << "m.row_size_ = " << m.row_size_ << " m.col_size_"
              << m.col_size_ << std::endl;
  }
  const int size = row_size_ * col_size_;  // 使用常量告诉编译器不用再计算
  for (int i = 0; i < size; i++) { values_[i] += m.values_[i]; }
  return *this;
}

Matrix Matrix::operator+(const Matrix &m) {
  if (row_size_ != m.row_size_ || col_size_ != m.col_size_) {
    std::cerr << "错误：矩阵大小不相等\n"
              << "位置：&Matrix::operator+(const Matrix &m)\n"
              << "row_size_ = " << row_size_ << " col_size_ = " << col_size_
              << std::endl
              << "m.row_size_ = " << m.row_size_ << " m.col_size_"
              << m.col_size_ << std::endl;
  }
  Matrix ret = *this;
  ret += m;
  return ret;
}

Matrix &Matrix::operator-=(const Matrix &m) {
  if (row_size_ != m.row_size_ || col_size_ != m.col_size_) {
    std::cerr << "错误：矩阵大小不相等\n"
              << "位置：&Matrix::operator-=(const Matrix &m)\n"
              << "row_size_ = " << row_size_ << " col_size_ = " << col_size_
              << std::endl
              << "m.row_size_ = " << m.row_size_ << " m.col_size_"
              << m.col_size_ << std::endl;
  }
  const int size = row_size_ * col_size_;  // 使用常量告诉编译器不用再计算
  for (int i = 0; i < size; i++) { values_[i] -= m.values_[i]; }
  return *this;
}

Matrix Matrix::operator-(const Matrix &m) {
  if (row_size_ != m.row_size_ || col_size_ != m.col_size_) {
    std::cerr << "错误：矩阵大小不相等\n"
              << "位置：&Matrix::operator-(const Matrix &m)\n"
              << "row_size_ = " << row_size_ << " col_size_ = " << col_size_
              << std::endl
              << "m.row_size_ = " << m.row_size_ << " m.col_size_"
              << m.col_size_ << std::endl;
  }
  Matrix ret = *this;
  ret -= m;
  return ret;
}

Matrix &Matrix::operator*=(const int k) {
  const int size = row_size_ * col_size_;
  for (int i = 0; i < size; i++) { values_[i] *= k; }
  return *this;
}

Matrix Matrix::operator*(const int k) {
  Matrix ret = *this;
  ret *= k;
  return ret;
}

Matrix &Matrix::operator/=(const int k) {
  if (k == 0.0) {
    std::cerr << "错误：矩阵不能除以 0\n"
              << "位置：&Matrix::operator/=(const int k)\n";
    exit(1);
  }
  const int size = row_size_ * col_size_;
  for (int i = 0; i < size; i++) { values_[i] /= k; }
  return *this;
}

Matrix Matrix::operator/(const int k) {
  Matrix ret = *this;
  ret /= k;
  return ret;
}

/*  矩阵操作  **************************************/
Matrix &Matrix::Transpose() {
  const int size = row_size_ * col_size_;
  double *copy = new double[size];
  memcpy(copy, values_, size * sizeof(double));
  std::swap(row_size_,
            col_size_);  // 后面的 row_size_ 和 col_size_ 是交换后的值
  for (int i = 0; i < row_size_; i++) {
    for (int j = 0; j < col_size_; j++) {
      values_[i * col_size_ + j] = copy[j * row_size_ + i];
    }
  }
  delete[] copy;
  return *this;
}

/*  extra operator reload functions *******************/
Vector operator*(const int k, const Vector &v) {
  // Vector result(v.orientation_);
  // result.size_ = v.size_;
  // result.values_ = new double[v.size_];
  // memcpy(result.values_, v.values_, v.size_ * sizeof(double));
  Vector result = v;
  result *= k;
  return result;
}

Matrix operator*(const int k, const Matrix &m) {
  Matrix result = m;
  result *= k;
  return result;
}

using namespace std;

int main() {
  Matrix m(3, 2, 1.1, 1.2, 2.1, 2.2, 3.1, 3.2);
  // Matrix n = Matrix(m);
  // // n.Print();
  // cout << endl;
  // n[1][1] = 9;
  // m.Print();
  // cout << endl;
  // n.Print();
  // m.Print();
  // m.Transpose();
  // m.Print();

  // Matrix n = 2 * m;
  // n.Print();

  Vector u(kHorizontal, 2, 1.0, 2.0);
  // Vector v = (Vector(u));
  Vector v = 3 * u;
  v.Print();
  v.Transpose();
  v.Print();
  // v[1] = 90;

  // u.Print();
  // v.Print();

  return 0;
}
