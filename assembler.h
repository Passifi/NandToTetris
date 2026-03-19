#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <assert.h>
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
} Token;

typedef struct Scanner {
  char *data;
  unsigned int position;
  unsigned int start;
} Scanner;

int isAtEnd();
char advance();
char peek();
void scan();
void number();
void string();
void initializeScanner(char *data);
void freeScanner();
void freeToken(Token t);
#endif
