#include "parser.h"
#include "assembler.h"
#include "dynamicArray.h"
#include <endian.h>
#define TARGET_NOT_FOUND -1

static Parser parser;

void initializeParser(Array tokens) {
  parser.tokens = tokens;
  initializeArray(&parser.instructions, sizeof(Instruction));
}

int isAtEndToken() { return parser.tokens.index == parser.index; }

Token advanceToken() {
  Token t;
  getValue(&t, parser.index++, &parser.tokens);
  return t;
}

Array *parse() {

  Token t = advanceToken();
  Instruction current = CMD_BASE;
  // detination operation source, semicolon, branch
  // while not newline
  while (!isAtEndToken()) {
    switch (t.type) {
    case DRegister:
      current |= SET_D;
      break;
    case ARegister:
      current |= SET_A;
      break;
    case Memory:
      current |= SET_M;
      break;
    case JGE:
      current |= CMP_GREATER_EQUAL;
      break;
    case JGT:
      current |= CMP_GREATER;
      break;
    case JNE:
      current |= CMP_NOT;
      break;
    case JLT:
      current |= CMP_LESS;
      break;
    case JLE:
      current |= CMP_LESS_EQUAL;
      break;
    case JMP:
      current |= CMP_ALWAYS;
      break;
    case SetAddress:
      t = advanceToken();
      // t must be a numeral here currenlty include a check
      current = t.value;
      break;
    case Newline:
      addValue(&current, &parser.instructions);
      current = CMD_BASE;
      break;
    default:
      break;
    }
    t = advanceToken();
  }
  return &parser.instructions;
}
int getTarget(Instruction *inst, Token *t) {
  switch (t->type) {
  case DRegister:
    *inst |= SET_D;
    break;
  case ARegister:
    *inst |= SET_A;
    break;
  case Memory:
    *inst |= SET_M;
    break;
  default:
    return TARGET_NOT_FOUND;
  }
  return 0;
}
int target(Instruction *inst) {
  Token t;
  int result;
  // needs to loop until you it hit equal sign IF you hit semicolon go back and
  // interpret as computation
  static int targetVals[] = {DRegister, ARegister, Memory};
  static int initialComputation[] = {Not, Minus};
  if (!match(targetVals, sizeof(targetVals))) {
    result = computation(inst);
  }

  return result;
}

int jmp(Instruction *inst);
int operator(Instruction *inst) {
  Token t;
  int result = 0;
  switch (t.type) {
  case Not:
    // look for source if no source found ERROR
    break;
  case And:

    break;
  case Or:
    break;
  case Plus:
    break;
  case Minus:
    break;
  default:
    return -1;
  }
  return result;
}
int computation(Instruction *inst) {
  Token t;
  int result = 0;
  switch (t.type) {
  case Not:
    // check for register and continue
    break;
  case Minus:

  // check for register and continue
  //
  case DRegister:
    // check for operator
    break;
  case Memory:
    // check for operator
  case ARegister:
    // check for operator
  default:
    result = -1;
  }
  return result;
}

int match(int *symbols, size_t size) {
  Token current = getCurrent();
  for (size_t i = 0; i < size; i++) {
    if (current.type == symbols[i]) {
      return 1;
    }
  }

  return 0;
}

Token getCurrent() {
  Token value;
  getValue(&value, parser.index, &parser.tokens);
  return value;
}
