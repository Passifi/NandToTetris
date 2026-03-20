#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <assert.h>
#include "dynamicArray.h"
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
enum TokenType {
  Identifier,
  T_eof,
  Assign,
  Plus,
  Minus,
  SetAddress,
  DRegister,
  ARegister,
  Memory,
  Number,
  And,
  Or,
  Not,
  Newline,
  Semicolon,
  JEQ,
  JGE,
  JNE,
  JLT,
  JLE,
  JGT,
  TT_END
};

typedef struct Token {
  char *literal;
  enum TokenType type;
  unsigned int value;
} Token;

typedef struct Scanner {
  char *data;
  unsigned int position;
  unsigned int start;
  size_t size;
} Scanner;

int isAtEnd();
char advance();
char peek();
Array* scan();
void number();
void string();
void initializeScanner(char *data,size_t size);
void freeScanner();
void freeToken(Token t);
#endif
