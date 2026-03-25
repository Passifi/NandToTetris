#include "assembler.h"
#include "dynamicArray.h"
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "utility.h"
void printArray(Array* arr) {
  printf("%d\n",arr->index); 
   Token t;
   for(int i = 0 ; i < arr->index; i++) {
   getValue(&t, i,  arr); 
    if(t.type == Number)  
      printf("Number: %d\n",t.value);
    else if(t.type != Newline) 
      printf("%s\n",t.literal); 
  }

  }

void printInstructions(Array* arr) {
  Instruction inst;
  for(int i = 0 ; i < arr->index; i++) {
   getValue(&inst, i,  arr); 
  printbinary(inst); 
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
  size_t size = fread(dataBuffer, sizeof(char), 1024, f /* ataBuffer */);
  initializeScanner(dataBuffer,size);
  Array* arr = scan();
  printArray(arr);
  initializeParser(*arr);
  Array* instructions = parse();
  printInstructions(instructions);  
  return 0;
}

int main(int argc, char **argv) {
  scanFile(argc,argv);
  return 0;
}
