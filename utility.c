#include "utility.h"
#include <string.h>

char** splitString(char* str, char delimiter) 
{
  char** result = NULL;
  int seperator = 0;
  size_t totalLength;
  for(size_t i; str[i]; i++) {
    if(str[i] == delimiter) {
      seperator = i;
    }   
    totalLength++;
  }
  result = (char**)malloc(sizeof(char**)*2);
  result[0] = (char*)malloc(sizeof(char)*seperator );
  memcpy( result[0], str, (size_t)seperator); 
  result[0][seperator-1] = '\0';

  memcpy( result[1], str+seperator+1, (size_t)(totalLength-seperator)); 
  return result;
}
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


