#include "assembler.h"
#include "dynamicArray.h"
#include <stdio.h>
#include <stdlib.h>

void printArray(Array* arr) {
   
   Token t;
   for(int i = 0 ; i < arr->index; i++) {
   getValue(&t, i,  arr); 
    printf("%s\n",t.literal); 
  }

  }

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
  Array* arr = scan();
  printArray(arr);
  return 0;
}

int main(int argc, char **argv) {
  scanFile(argc,argv);
  return 0;
}
