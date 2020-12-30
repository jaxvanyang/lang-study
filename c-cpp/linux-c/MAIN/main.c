#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "helper.h"
#include "statistic.h"
#include "sort.h"


int main(int argc, char *argv[]) {
    printStrArr(argv, argc);

    putchar('\n');

    printf("%d\n", strToInt("abc"));

    printf("%lf\n", strToDouble("123.8"));

	int arr[] = {3, 2, 1};
	printf("%lf\n", getIntArrAverage(arr, 3));

	insertionSort(arr, 3);
	printIntArr(arr,3 );
}
