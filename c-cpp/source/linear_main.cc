#include "linear_algebra.h"

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
