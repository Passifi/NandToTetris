#include "parser.h"
#include "assembler.h"
#include "dynamicArray.h"
#include <endian.h>
#define TARGET_NOT_FOUND -1
#define SUCCESS 0 
#define PARSING_ERROR -12
static Parser parser;
static unsigned int line;

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

Token peekToken() {
   Token t;
  getValue(&t,parser.index+1,&parser.tokens);
  return t;

}

Array* parse() {
  
  Instruction inst;
  while(target(&inst) != PARSING_ERROR) {
    advanceToken();
    addValue(&inst, &parser.instructions); 
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
int target(Instruction* inst) {
  Token t = getCurrent();
  static int targetVals[] ={DRegister,ARegister,Memory}; 
  int result = 0; 
  int foundTarget = 0; 
  while(match(targetVals,3)) {
    if(peekToken().type == Semicolon) {
      if(foundTarget) {
        printf("Expected = and computation after destination\n");
        return PARSING_ERROR;
      } 
      result = computation(inst);
      break; 
    }
    foundTarget =1;
       
    switch(t.type) {
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
        break;
    }   

    t = advanceToken();
  }  
  if(foundTarget) {
    if(!(peekToken().type == Assign)) {
      printf("Expected = after destination declaration\n");
      return PARSING_ERROR; 
    }
    else {
      t = advanceToken();
    }
  }
  result = computation(inst);
  return result;
}
int jmp(Instruction* inst);
int computation(Instruction* inst) {
  return SUCCESS;
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
