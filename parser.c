#include "parser.h" 
#include "assembler.h"
#include "dynamicArray.h"
#define TARGET_NOT_FOUND -1
#define SUCCESS 0 
#define PARSING_ERROR -12
static Parser parser;
static unsigned int line;

void initializeParser(Array tokens) {
  parser.tokens = tokens;
  initializeArray(&parser.instructions,  sizeof(Instruction));

}

int isAtEndToken() {
  return parser.tokens.index == parser.index;
}

Token advanceToken() {
  Token t;
  getValue(&t,parser.index++,&parser.tokens);
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
int getTarget(Instruction* inst, Token* t) {
    switch(t->type) {
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

int match(int* symbols, size_t size) {
  Token current = getCurrent();
  for (size_t i = 0; i < size; i++)
  {
    if(current.type == symbols[i]) {
      return 1;
    } 
  }
  
  return 0;
}


Token getCurrent() {
  Token value;
  getValue(&value,parser.index,&parser.tokens);
  return value;
}

