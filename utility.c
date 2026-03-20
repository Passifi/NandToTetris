#include "utility.h"

void printbinary(int value) {
   int mask = 0x8000;
  for(int i = 0; i < 16; i++) {
    int current = value &mask;
    current = current >> (15-i);
    printf("%d",current);
    mask = mask>>1;
  }
  printf("\n");
}


