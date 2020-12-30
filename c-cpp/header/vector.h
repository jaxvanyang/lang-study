#pragma once
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

enum Orientation { VERTICAL, HORIZONTAL };

class Vector {
private:
    double *components;
    int size;
    Orientation orientation;

public:
    friend class Matrix;

    Vector(const vector<double> &args, Orientation orientation = VERTICAL);
    Vector(Orientation orientation = VERTICAL);
    Vector(double x, Orientation orientation = VERTICAL);
    Vector(double x, double y, Orientation orientation = VERTICAL);
    Vector(double x, double y, double z, Orientation orientation = VERTICAL);
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

inline Vector &Vector::operator*=(int n) {
    if (size <= 0) {
        cerr << "Error: Cannot multiply invaild vector.\n";
        exit(0);
    }
    for (int i = 0; i < size; i++) {
        components[i] *= n;
    }
    return *this;
}

inline Vector operator*(int n, Vector &v) {
    return v * n;
}

inline int Vector::getSize() {
    return size;
}

inline Orientation Vector::getOrientation() {
    return orientation;
}

inline double &Vector::operator[](int n) {
    if (0 <= n && n < size) {
        return components[n];
    }
    cerr << "Error: Index exceed limit.\n" << endl;
    exit(-1);
}

inline bool Vector::isValid() {
    return size > 0;
}