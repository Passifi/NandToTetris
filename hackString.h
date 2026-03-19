#ifndef HACKSTRING_H
#define HACKSTRING_H
#include <cstring>
#include <string.h>
#include <stdlib.h>
#define STR_SIZE_BASE 16

typedef struct Hackstring {

  char* str;
  size_t size;
  size_t bufferSize;
} Hackstring;

int emptyStr(Hackstring* str) {
  str->size = 0;
  str->bufferSize = STR_SIZE_BASE;

  str->str = NULL; 
}

int resize(Hackstring* str) {
  char* newPointer = NULL;
  newPointer = (char*)realloc(str->str,str->bufferSize*2);
  if(newPointer == NULL) {
    return -1;
  } 
  str->bufferSize *= 2;
  str->str = newPointer;
  return 0;
}

int initStr(Hackstring* str,const char* string,size_t size) {
  str->size = size;
  str->str = (char*)malloc(sizeof(char)*str->size);
  memcpy(str->str,string, size);
}

int appendStr(Hackstring* str, char c) {
  if(str->size >= str->bufferSize) {
   // resizeStr(str); 
  }
  str->str[str->size] = c;
  str->size++;
}
int concatenate(Hackstring* dest, Hackstring* str) {
  if(dest->size + str->size > dest->bufferSize) {
   // resizeStr(dest); 
  }
  memcpy(str->str+str->size,str,str->size);
  dest->size = dest->size + str->size - 1;
}


#endif
