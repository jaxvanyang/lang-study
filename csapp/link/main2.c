/**
 * from CSAPP code/link/main2.c
 */

#include <stdio.h>
#include "vector.h"

int x[2] = {1, 2};
int y[2] = {3, 4};
int z[2];

int main() {
  // using addvec only causes the compiler to copy addvec.o only
  addvec(x, y, z, 2);
  printf("z = [%d %d]\n", z[0], z[1]);
  return 0;
}