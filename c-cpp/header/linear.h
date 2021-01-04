/* 线性代数
 * 包括向量和向量的线性运算
 * 包括矩阵和矩阵的线性运算
 */

#include <vector>

enum Orientation { kVertical, kHorizontal };

/* 向量的大小在初始化后就不应该改变
 */
class Vector {
 private:
  double *components;
  int size;
  Orientation orientation;

 public:
  friend class Matrix;

  Vector(const std::vector<double> &args, Orientation orientation = kVertical);
  Vector(Orientation orientation = kVertical);
  Vector(double x, Orientation orientation = kVertical);
  Vector(double x, double y, Orientation orientation = kVertical);
  Vector(double x, double y, double z, Orientation orientation = kVertical);
  /*
   * 不加 const 编译报错可能是因为在其它函数中被调用
   * 但是拷贝的是一个临时变量
   * C++ 中不允许使用非 const 方式引用临时变量
   * 因为引用是为了修改（其实还有提升效率），修改临时变量没有意义（可能吧）
   */
  Vector(const Vector &v);
  ~Vector();
  Vector operator+(Vector &v);
  void print();
  Vector operator*(int n);
  inline Vector &operator*=(int n);
  inline int getSize();
  inline Orientation getOrientation();
  inline double &operator[](int n);
  inline bool isValid();
  Vector operator+(Vector v);
  Vector &operator+=(Vector v);
};