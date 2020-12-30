#include "sort.h"

namespace my_sort {

    template <typename T>
    void insertion_sort(T *arr, int size) {
        for (int i = 1; i < size; i++) {
            T key = arr[i];
            int p = i - 1;
            while (p >= 0 && arr[p] > key) {  // ERR 居然把 key 写成了 arr[p + 1]
                arr[p + 1] = arr[p];
                p--;
            }
            arr[p + 1] = key;
        }
    }

    template <typename T>
    void insertion_sort(vector<T> &arr) {
        int size = arr.size();
        for (int i = 1; i < size; i++) {
            T key = arr[i];
            int p = i - 1;
            while (p >= 0 && arr[p] > key) {
                arr[p + 1] = arr[p];
                p--;
            }
            arr[p + 1] = key;
        }
    }

}  // namespace my_sort