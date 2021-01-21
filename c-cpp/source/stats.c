#include <stdio.h>
#include <stdlib.h>

#include "helper.h"
#include "statistic.h"

int main(int argc, char *argv[]) {
  parseParameter(argc, argv);

  int size = writeData();
}