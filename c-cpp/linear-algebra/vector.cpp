#include "vector.h"

Vector::Vector(Orientation orientation) : orientation(orientation) {
    components = nullptr;
    size = 0;
}

Vector::Vector(const vector<double> &args, Orientation orientation) : orientation(orientation) {
    size = args.size();
    components = new double[size];
    for (int i = 0; i < size; i++) {
        components[i] = args[i];
    }
}

Vector::Vector(double x, Orientation orientation) : orientation(orientation) {
    size = 1;
    components = new double[1];
    components[0] = x;
}

Vector::Vector(double x, double y, Orientation orientation) : orientation(orientation) {
    size = 2;
    components = new double[2];
    components[0] = x;
    components[1] = y;
}

Vector::Vector(double x, double y, double z, Orientation orientation) : orientation(orientation) {
    size = 3;
    components = new double[3];
    components[0] = x;
    components[1] = y;
    components[2] = z;
}

Vector::~Vector() {
    delete[] components;
}

Vector Vector::operator+(Vector &v) {
    if (size == v.size && orientation == v.orientation) {
        vector<double> args(size);
        for (int i = 0; i < size; i++) {
            args[i] = components[i] + v.components[i];
        }
        Vector newV(args, orientation);
        return newV;
    }
    cerr << "Error: Vector operands don't match each other.\n";
    exit(0);
}

void Vector::print() {
    if (orientation == VERTICAL) {
        for (int i = 0; i < size; i++) {
            cout << left << setw(5) << '|' << setw(5) << components[i] << "|\n";
        }
    } else {
        cout << '(';
        if (size > 0) {
            cout << components[0];
        }
        for (int i = 1; i < size; i++) {
            cout << ", " << components[i];
        }
        cout << ")\n\n";
    }
}

Vector Vector::operator*(int n) {
    if (size <= 0) {
        cerr << "Error: Cannot multiply invalid vector.\n";
        exit(0);
    }
    Vector newV = *this;
    for (int i = 0; i < size; i++) {
        newV.components[i] *= n;
    }
    return newV;
}

Vector Vector::operator+(Vector v) {
    if (isValid() && size == v.size && orientation == v.orientation) {
        Vector newV = v;
        for (int i = 0; i < size; i++) {
            newV[i] += (*this)[i];
        }
        return newV;
    } else {
        cerr << "Error: Invalid vector plus.\n";
        exit(-1);
    }
}

Vector &Vector::operator+=(Vector v) {
    if (isValid() && size == v.size && orientation == v.orientation) {
        for (int i = 0; i < size; i++) {
            (*this)[i] += v[i];
        }
        return *this;
    } else {
        cerr << "Error: Invalid vector += operation.\n";
        exit(-1);
    }
}

Vector::Vector(const Vector &v) {
    size = v.size;
    components = new double[size];
    for (int i = 0; i < size; i++) {
        components[i] = v.components[i];    // 也不能直接用数组运算符
    }
    orientation = v.orientation;
    // cout << "copy vector\n";
    // print();
}