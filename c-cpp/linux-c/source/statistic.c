#include "statistic.h"

double getIntArrAverage(int arr[], int size) {
    if (size <= 0) {
        fprintf(stderr, "No element in arr!\n");
        return 0.0;
    }
    double ret = 0.0;
    for (int i = 0; i < size; i++) {
        ret += arr[i];
    }
    return ret / size;
}

double getDoubleArrAverage(double arr[], int size) {
    if (size <= 0) {
        fprintf(stderr, "No element in arr!\n");
        return 0.0;
    }
    double ret = 0.0;
    for (int i = 0; i < size; i++) {
        ret += arr[i];
    }
    return ret / size;
}

int writeData() {
    writeInputToFile("stats.data");
}

// TODO: 完善 packData
Data packData(double *arr, const int size) {
    Data data;
    data.size = size;
    return data;
}

void parseParameter(const int argc, char *argv[]) {
    double *data = (double *)calloc(argc - 1, sizeof(double));
    int size = argc - 1;
    double total = 0.0, average = 0.0, maxValue = 0.0, minValue = 0.0;

    for (int i = 1, j = 0; i < argc; i++, j++) {
        data[j] = strToDouble(argv[i]);
    }

    if (size > 0) { maxValue = minValue = total = data[0]; }
    for (int i = 1; i < size; i++) {
        maxValue = data[i] > maxValue ? data[i] : maxValue;
        minValue = data[i] < minValue ? data[i] : minValue;
        total += data[i];
    }
    if (size > 0) { average = total / size; }

    if (size == 0) {
        printf("No data in command parameter.\n");
    } else {
        printf("size is %d\n", size);
        printf("total is %lf\n", total);
        printf("average is %lf\n", average);
        printf("maxValue is %lf\n", maxValue);
        printf("minValue is %lf\n", minValue);
    }
}