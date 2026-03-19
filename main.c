#include "assembler.h"
#include "dynamicArray.h"
#include <stdio.h>
#include <stdlib.h>

int scanFile(int argc, char **argv) {

  if (argc < 2) {
    printf("Please provide a proper file path\n");
    return -1;
  }
  FILE *f;
  char dataBuffer[1024];
  f = fopen(argv[1], "r");
  fread(dataBuffer, sizeof(char), 1024, f /* ataBuffer */);
  initializeScanner(dataBuffer);
  scan();
}

int main(int argc, char **argv) {

  Array arr;
  initializeArray(&arr, sizeof(int));
  int value;
  for (int i = 0; i < 1000000; i++) {
    addValue(&i, &arr);
    getValue(&value, i, &arr);
    printf("%d\n", value);
    assert(i == value);
  }
  freeArray(&arr);
  return 0;
}
