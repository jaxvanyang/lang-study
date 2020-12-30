#include "matrix.h"
#include "vector.h"

int main() {
    vector<vector<double>> args = {{0, -1}, {1, 0}};
    Matrix m(args, true);
    m.print();
    Matrix n({{1, 1}, {0, 1}}, true);
    n.print();

    Matrix res = n * m;
    res.print();

    Matrix a({{1, 2, 3}}, true);
    Matrix b({{4}, {5}, {6}}, true);
    a.print();
    b.print();

    res = a * b;
    res.print();
}