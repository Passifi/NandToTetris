#include "dynamicArray.h"
int initializeArray(Array *array, size_t elementSize) {
  array->size = BASE_SIZE;
  array->index = 0;
  array->value = malloc(elementSize * array->size);
  array->elementSize = elementSize;
  if (array->value == NULL) {
    return -1;
  } else {
    return 0;
  }
}

int resizeArray(Array *array) {

  array->size *= 2;
  void *result = realloc(array->value, (array->size) * array->elementSize);
  if (result == NULL) {
    return -1;
  }
  array->value = (int *)result;
  return 0;
}

int addValue(void *value, Array *array) {
  int result = 0;
  if (array->size == array->index) {
    result = resizeArray(array);
    if (result != 0) {
      return result;
    }
  }
  memcpy((char *)array->value + array->index * array->elementSize, value,
         array->elementSize);
  array->index++;
  return result;
}

int getValue(void *dest, size_t position, Array *array) {
  if (position < array->index) {
    memcpy(dest, (char *)array->value + position * array->elementSize,
           array->elementSize);
    return 0;
  } else
    return -1;
}

void freeArray(Array *array) {
  free(array->value);
  array->value = NULL;
  array->size = 0;
  array->index = 0;
}

int testArray() {
  Array arr;
  initializeArray(&arr, sizeof(int));
  int value;
  int result =0;  
  for (int i = 0; i < 1000000; i++) {
    addValue(&i, &arr);
    getValue(&value, i, &arr);
    if(value != i) {
      result = -1;
      break;
    } 
  }
  freeArray(&arr);
  return result;
}

