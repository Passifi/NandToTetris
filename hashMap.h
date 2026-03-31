#ifndef HASHMAP_H
#define HASHMAP_H
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynamicArray.h"

typedef struct Node {
  int hash;
  void* value;
  Node* next;
} Node;

inline void initializeNode(Node* node,int hash,void* value, size_t valueSize) {
  node->next = NULL;
  node->hash = hash;
  node->value = malloc(sizeof(char)*valueSize);
  memcpy(node->value, value,  valueSize); 
}

inline void addNode(Node* root, int hash, void* value, size_t valueSize) {
  Node* n = (Node*)malloc(sizeof(Node));
  initializeNode(n,  hash, value,  valueSize);
  while(root->next != NULL) 
    root = root->next;
  root->next = n;
}

inline void freeNodes(Node* root) {
  Node *current = root->next;
  while(current != NULL) {
    Node* next = current->next;
    free(current->value); 
    free(current);
    current = next;
  }
}

typedef struct Hashmap {
  int (*hash)(void* value,size_t elementSize);
  size_t dataSize;
  size_t mapSize;
  void* data; 
} Hashmap;

inline int keyGen(void* value,size_t elementSize ) {
  int result = 0; 
  for(int i = 0 ; i < elementSize; i++) {
    result += *((char*)value + i);
  }    
  return result;
}
inline int initializeHashmap(Hashmap* map, size_t valueSize, int(*keyGenerator)(void* value, size_t elementSize )) {
  if(keyGenerator != NULL) {
    map->hash = keyGenerator; 
  }
  else {
    map->hash = keyGen;
  }
  map->dataSize = valueSize;
  map->mapSize = 128;
  map->data = malloc(map->mapSize*sizeof(char));
  return 0;
}

inline int getValue(Hashmap* map,void* key,void* value) {
  int index = map->hash(key,map->dataSize) % map->dataSize;
  // do comparisons here 
  if( map->values[index] == NULL) {

  } 
  memcpy( value,(char*)map->data+ map->dataSize*index, map->dataSize);
  return 0;
}


#endif // !HASHMAP_H
