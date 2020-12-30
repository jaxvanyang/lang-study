#include "helper.h"

using namespace std;

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

bool isDigit(char ch) {
    return '0' <= ch && ch <= '9';
}

int strToInt(char *str) {
    int len = strlen(str);
    int ret = 0;
    int k = 1;
    for (int i = len - 1; i >= 0; i--, k *= 10) {
        if (!isDigit(str[i])) {
            fprintf(stderr, "Cannot transfer \"%s\" to int!\n", str);
            return -1;
        }
        ret += (str[i] - '0') * k;
    }
    return ret;
}

double strToDouble(char *str) {
    int len = strlen(str);
    double ret = 0.0;
    double k = 1.0;
    int i = len - 1;
    for (; i >= 0 && str[i] != '.'; i--, k *= 10) {
        if (!isDigit(str[i])) {
            fprintf(stderr, "Cannot transfer \"%s\" to double!\n", str);
            return -1.0;
        }
        ret += (str[i] - '0') * k;
    }
    if (i >= 0) {
        ret /= k;
        k = 1.0;
        char *tmp = (char *)calloc(i, sizeof(char));
        strncpy(tmp, str, i);
        ret += strToInt(tmp);
    }
    return ret;
}

// 返回写入文件的行数
int writeInputToFile(char *fileName) {
    char *str = (char *)calloc(10, sizeof(char));
    char ch;
    int cnt = 0;
    FILE *file = fopen(fileName, "w");
    while (1) {
        scanf("%s", str);
        if ((ch == getchar()) == EOF || str[0] == '\0') break;
        cnt++;
        fprintf(file, "%s\n", str);
        str[0] = '\0';
    }
    fclose(file);
    return cnt;
}

/* 将输入写入到 input 文件中
 * 返回写入的行数
 */
int writeInput() {
    return writeInputToFile("input.tmp");
}