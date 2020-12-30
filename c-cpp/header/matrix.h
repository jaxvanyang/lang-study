#pragma once
#include "vector.h"

class Matrix {
private:
    int row, col;
    Vector *vectors;

public:
    friend Vector operator*(Vector v, Matrix m);
    friend Vector operator*(Matrix m, Vector v);

    Matrix(vector<Vector> vectors);
    Matrix(const vector<vector<double>> &args, bool flag);
    ~Matrix();
    inline Vector &operator[](int n);
    inline void print();
    inline bool isValid();
    Matrix operator*(int n);
    Matrix &operator*=(int n);
    Matrix operator+(Matrix m);
    Matrix(const Matrix &m);
    // inline Matrix operator=(const Matrix &m);

    Matrix operator*(Matrix &m);
};

Vector operator*(Vector v, Matrix m);
Vector operator*(Matrix m, Vector v);
inline Matrix operator*(int n, Matrix m);

inline Vector &Matrix::operator[](int n) {
    if (0 <= n && n < row) {
        return vectors[n];
    }
    cerr << "Error: Index exceed limit.\n";
    exit(0);
}

inline void Matrix::print() {
    for (int i = 0; i < row; i++) {
        cout << left << setw(5) << '|';
        for (int j = 0; j < col; j++) {
            cout << setw(5) << vectors[i][j];
        }
        cout << "|\n";
    }
    cout << endl;
}

inline bool Matrix::isValid() {
    return 0 < row && 0 < col;
}

inline Matrix operator*(int n, Matrix m) {
    return m * n;
}

// TODO: 重载 = 操作符后更加麻烦，数据直接顺序颠倒，以后不能再使用不完善的指针来维护数据了
// 成员通通用类来管理
// inline Matrix Matrix::operator=(const Matrix &m) {
//     cout << 1;
//     return Matrix(m);
// }