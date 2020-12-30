#include "matrix.h"

Matrix::Matrix(vector<Vector> vectors) {
    int l1 = vectors.size();
    if (l1 <= 0) {
        cerr << "Error: Initial vectors contains less than 1 vector.\n";
        exit(-1);
    }
    int l2 = vectors[0].getSize();
    if (l2 <= 0) {
        cerr << "Error: Initial vectors has vector having no component.\n";
        exit(-1);
    }
    for (int i = 1; i < l1; i++) {
        if (vectors[i].getSize() != l2) {
            cerr << "Error: Initial vectors contain vectors having different lengthes.\n";
            exit(-1);
        }
    }
    Orientation orientation = vectors[0].orientation;
    for (int i = 1; i < l1; i++) {
        if (vectors[i].orientation != orientation) {
            cerr << "Error: Initial vectors have different orientation.\n";
            exit(-1);
        }
    }

    bool isVertical = orientation == VERTICAL;
    row = isVertical ? l2 : l1;
    col = isVertical ? l1 : l2;
    this->vectors = new Vector[row];
    for (int i = 0; i < row; i++) {
        this->vectors[i].orientation = HORIZONTAL;
        this->vectors[i].size = col;
        this->vectors[i].components = new double[col];
    }

    if (isVertical) {
        for (int i = 0; i < col; i++) {
            for (int j = 0; j < row; j++) {
                this->vectors[j][i] = vectors[i][j];
            }
        }
    } else {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                this->vectors[i][j] = vectors[i][j];
            }
        }
    }
}

Matrix::~Matrix() {
    delete[] vectors;
}

Vector operator*(Matrix m, Vector v) {
    if (m.col != v.getSize() || v.getOrientation() != VERTICAL) {
        cerr << "Error: Imcompatible multiply.\n";
        exit(-1);
    }
    vector<double> args;
    for (int i = 0; i < m.row; i++) {
        double sum = 0;
        for (int j = 0; j < m.col; j++) {
            sum += m[i][j] * v[j];
        }
        args.push_back(sum);
    }
    return Vector(args);
}

Vector operator*(Vector v, Matrix m) {
    if (m.row != v.getSize() || v.getOrientation() != HORIZONTAL) {
        cerr << "Error: Imcompatible multiply.\n";
        exit(-1);
    }
    vector<double> args;
    for (int i = 0; i < m.col; i++) {
        double sum = 0;
        for (int j = 0; j < m.row; j++) {
            sum += m[j][i] * v[j];
        }
        args.push_back(sum);
    }
    return Vector(args, HORIZONTAL);
}

Matrix Matrix::operator*(int n) {
    if (isValid()) {
        Matrix newM = *this;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                newM[i][j] *= n;
            }
        }
        return newM;
    } else {
        cerr << "Error: Invalid matrix.\n";
        exit(-1);
    }
}

Matrix &Matrix::operator*=(int n) {
    if (isValid()) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                (*this)[i][j] *= n;
            }
        }
        return *this;
    } else {
        cerr << "Error: Invalid matrix.\n";
        exit(-1);
    }
}

Matrix Matrix::operator+(Matrix m) {
    if (isValid() && m.isValid() && row == m.row && col == m.col) {
        Matrix newM = m;
        for (int i = 0; i < row; i++) {
            newM[i] += (*this)[i];
        }
        return newM;
    } else {
        cerr << "Error: invalid matrix + operation.\n";
        exit(-1);
    }
}

// TODO: 找出通过 = 初始化不会被调用的原因
Matrix::Matrix(const Matrix &m) {
    row = m.row;
    col = m.col;
    /*
     * 陷入绝境
     * 用的是默认构造函数
     * 不仅 Matrix 用的是默认拷贝构造函数，Vetor 也是
     * 暂时先手写吧
     * 手写完成
     * 但是不知道为什么用 = 来初始化只会调用默认拷贝构造函数了
     * 可以显式调用拷贝构造函数
     */
    vectors = new Vector[row];
    for (int i = 0; i < row; i++) {
        // vectors[i] = m.vectors[i];
        // vectors[i].components = new double[col];
        // for (int j = 0; j < col; j++)
        // {
        //     vectors[i][j] = m.vectors[i].components[j];
        // }
        vectors[i] = Vector(m.vectors[i]);
    }
    // memcpy(vectors, m.vectors, row * sizeof(Vector));
    // cout << &(m.vectors[0]) << endl << &vectors[0];
}

Matrix::Matrix(const vector<vector<double>> &args, bool flag) {
    row = args.size();
    if (row <= 0) {
        cerr << "Error: Invalid initial args." << endl
             << "Position: Matrix(const vector<vector<double>> &args)." << endl;
        exit(-1);
    }
    col = args[0].size();
    for (int i = 1; i < row; i++) {
        if (args[i].size() != col) {
            cerr << "Error: Invalid initial args.\n"
                 << "Position: Matrix(const vector<vector<double>> &args)." << endl;
            exit(-1);
        }
    }

    vectors = new Vector[row];
    for (int i = 0; i < row; i++) {
        vectors[i] = Vector(args[i], HORIZONTAL);
    }
    // TODO: 出现了致命 BUG，应该是 Vetor 的构造函数出了问题
    // 吊诡的是之前并没有出现问题，现在回滚了版本仍然出错
    // cout << endl << "Test:\n";
    // for (int i = 0; i < row; i++) {
    //     for (int j = 0; j < col; j++) {
    //         cout << (*this)[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << "end\n";
}

Matrix Matrix::operator*(Matrix &m) {
    if (isValid() && m.isValid() && col == m.row) {
        vector<vector<double>> args(row, vector<double>(m.col, 0));
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < m.col; j++) {
                for (int k = 0; k < col; k++) {
                    args[i][j] += (*this)[i][k] * m[k][j];
                }
            }
        }
        return Matrix(args, true);
    }
    cerr << "Error: Matrix multiply dismatch.\n"
         << "Position: Matrix operator*(Matrix &m).\n";
    exit(-1);
}