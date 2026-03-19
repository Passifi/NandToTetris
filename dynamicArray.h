#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define BASE_SIZE 1024
typedef struct Array {
  void *value;
  size_t size;
  size_t elementSize;
  size_t index;
} Array;

int initializeArray(Array *array, size_t elementSize);
int resizeArray(Array *array);
int addValue(void *value, Array *array);
int getValue(void *dest, size_t position, Array *array);
void freeArray(Array *array);
int testArray();
#endif
