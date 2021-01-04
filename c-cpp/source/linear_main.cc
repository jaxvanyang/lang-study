#include "linear_algebra.h"

using namespace std;

int main() {
  Matrix m;
  cout << "empty matrix:\n";
  m.Print();
  m = Matrix(3, 1, 2.0, 3.0, 4.0);
  // cout << "3 row 1 col matrix:\n";
  // auto copy = m.get_col_vector_copy(0);
  // for (auto item : copy) { cout << item << endl; }
  // auto row = m.get_row_vector_copy(2);
  // for (auto item : row) { cout << item << endl; }
  // m.get_item(2, 0) = 99;
  // m.Print();

  Matrix copy = m.Copy();
  cout << "this is copy:\n";
  copy.Print();

  cout << "copy changed:\n";
  copy.Transpose();
  copy.Print();

  cout << "let's see prototype:\n";
  m.Print();
  
  // m.Print();
  // Matrix n = m;
  // cout << "copy matrix:\n";
  // n.Print();
  // n.Transpose();
  // cout << "copy transpost:\n";
  // n.Print();
  // cout << "see protype:\n";
  // m.Print();

  return 0;
}
