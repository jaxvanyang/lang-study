#include "helper.h"

void printIntArr(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

void printStrArr(char *arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", arr[i]);
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

int writeInput() {
    return writeInputToFile("input");
}