#ifndef PARSER_H
#define PARSER_H
#include "assembler.h"
#include "dynamicArray.h"
#include <stdint.h>
#include <stdlib.h>

#define SET_M       0b0000000001000
#define SET_D       0b0000000010000
#define SET_A       0b0000000100000
#define ZERO_D      0b0100000000000
#define NEGATE_D    0b0010000000000
#define ZERO_A      0b0001000000000
#define NEGATE_A    0b0000100000000
#define NEGATE_OUT  0b0000001000000
#define ADD_VALUES  0b0000010000000
#define USE_MEMORY  0b1000000000000
#define CMP_GREATER 0b0000000000001
#define CMP_EQUAL   0b0000000000010
#define CMP_LESS    0b0000000000100
#define CMP_NOT CMP_GREATER | CMP_LESS
#define CMP_LESS_EQUAL CMP_EQUAL | CMP_LESS
#define CMP_GREATER_EQUAL CMP_EQUAL | CMP_GREATER
#define CMP_ALWAYS CMP_GREATER | CMP_LESS | CMP_EQUAL
#define CMD_BASE 0b1110000000000000

typedef uint16_t Instruction;

typedef struct Parser {
  size_t index;
  size_t size;
  Array tokens;
  Array instructions;
} Parser;

void initializeParser(Array tokens);
Array *parse();
int isAtEndToken();
Token advanceToken();
Token peekToken();
int target(Instruction* inst);
int branch(Instruction* inst);
int computation(Instruction* inst);
int match(int* symbols, size_t size);
int peekMatch(int* symbols, size_t size);
Token getCurrent();
#endif // !PARSER_H
