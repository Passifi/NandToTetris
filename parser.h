#ifndef PARSER_H
#define PARSER_H
#include "dynamicArray.h"
#include "assembler.h"
#include <stdint.h>
#include <stdlib.h> 

#define SET_M 0b0001000
#define SET_D 0b0010000
#define SET_A 0b0100000
#define COMP_SUB 0b1000
#define COMP_ADD 0b1000
#define COMP_NOT 0b1000
#define COMP_ZERO 0b1000
#define CMP_GREATER 0b1
#define CMP_EQUAL   0b10
#define CMP_LESS    0b100
#define CMP_NOT     CMP_GREATER | CMP_LESS
#define CMP_LESS_EQUAL     CMP_EQUAL | CMP_LESS
#define CMP_GREATER_EQUAL  CMP_EQUAL | CMP_GREATER
#define CMP_ALWAYS     CMP_GREATER | CMP_LESS | CMP_EQUAL
#define CMD_BASE 0b1110000000000000

typedef uint16_t Instruction;

typedef struct Parser {
  size_t index;
  size_t size;
  Array tokens;
  Array instructions;  
} Parser;

void initializeParser(Array tokens);
Array* parse();
int isAtEndToken();
Token advanceToken();
Token peekToken();
int target(Instruction* inst);
int branch(Instruction* inst);
int computation(Instruction* inst);
int match(int* symbols, size_t size);
Token getCurrent();
#endif // !PARSER_H
