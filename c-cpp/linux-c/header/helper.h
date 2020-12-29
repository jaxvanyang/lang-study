#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BOOL
#define BOOL
#define bool int
#define true 1
#define false 0
#endif

void printIntArr(int arr[], int size);
void printStrArr(char *arr[], int size);

// TODO: 改写成内联函数
bool isDigit(char ch);

int strToInt(char *str);
double strToDouble(char *str);

int writeInputToFile(char *fileName);
int writeInput();