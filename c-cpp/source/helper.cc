#include "helper.h"

using namespace std;

namespace my_helper {

    template <typename T>
    void printArr(const T *arr, const int &size) {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << ' ';
        }
        cout << endl;
    }

    template <typename T>
    void printArr(const vector<T> &arr) {
        for (const T &each : arr) {
            cout << each << ' ';
        }
        cout << endl;
    }

    template <typename T>
    void printMatrix(T **matrix, const int &rowSize, const int &colSize) {
        for (int row = 0; row < rowSize; row++) {
            printArr((T *)matrix + row * rowSize, colSize);
        }
    }

    template <typename T>
    void printMatrix(const vector<vector<T>> &matrix) {
        for (const vector<T> &row : matrix) {
            printArr(row);
        }
    }

}  // namespace my_helper
