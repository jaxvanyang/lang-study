#include "linear_algebra.h"

using namespace std;

int main() {
  // Vector u;
  // u.Print();
  // u = Vector(kHorizontal, 3, 1.0, 2.0, 3.0);
  // u.Print();

  // Vector v = Vector(u);
  // v.Transpose();
  // v.Print();

  Matrix m;
  m.Print();
  m = Matrix(2, 1, 1.1, 1.2);
  m.Print();

  Matrix n = Matrix(m);
  n.Transpose();
  n.Print();

  
  return 0;
}
