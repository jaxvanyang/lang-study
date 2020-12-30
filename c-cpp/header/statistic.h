#pragma once

#include <stdio.h>
#include "helper.h"

typedef struct Data_{
    int size;
    double total;
    double average;
    double maxValue;
    double minValue;
} Data;

double getIntArrAverage(int arr[], int size);

int writeData();

Data packData(double *arr, const int size);

void parseParameter(const int argc, char *argv[]);
