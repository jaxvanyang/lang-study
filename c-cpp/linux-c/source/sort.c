#include "sort.h"

void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int p = i - 1;
        while (p >= 0 && arr[p] > key) {
            arr[p + 1] = arr[p];
            p--;
        }
        arr[p + 1] = key;
    }
}