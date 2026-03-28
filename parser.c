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
  getValue(&t,parser.index,&parser.tokens);
  return t;

}

Array* parse() {
  Instruction inst;
  while(target(&inst) != PARSING_ERROR && !isAtEndToken()) {
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
  Token t = advanceToken();
  if(t.type == Newline) {
    t = advanceToken();
  }
  printf("%s\n",t.literal);
  static int targetVals[] ={DRegister,ARegister,Memory}; 
  static int computationVals[] ={Not,Plus,Minus,Or,And}; 
  int result = 0; 
  int foundTarget = 0; 
  if(match(computationVals,5)) {
    return computation(inst);
  }
  while(match(targetVals,3)) {
    printf("Target Value found\n");
    if(peekToken().type == Semicolon) {
      if(foundTarget>1) {
        printf("1.Expected = after desitination\n Error in Line: %d\n",t.line);
         
        return PARSING_ERROR;
      } 
      advanceToken();
      result = computation(inst);
      break; 
    }
       
    switch(t.type) {
      case DRegister:
        if(peekMatch(computationVals,5)) {
          return computation(inst);
        }
        else { 
          *inst |= SET_D;
        }
      break; 
      case ARegister:
        if(peekMatch(computationVals,5)) {
          return computation(inst);
        }
     
        *inst |= SET_A;
      break; 
      case Memory: 
        if(peekMatch(computationVals,5)) {
          return computation(inst);
        }
     
        *inst |= SET_M;
      break; 
      default:
        break;
    }   
    
    foundTarget++;
    t = advanceToken();
  }  
  if(foundTarget) {
    if(t.type != Assign) {
        printf("2.Expected = and computation after destination\n Error in Line: %d\n",t.line);
       
      return PARSING_ERROR; 
    }
  }
  result = computation(inst);
  return result;
}
int jmp(Instruction* inst);
int computation(Instruction* inst) {
  printf("Jumped into computation\n");
  
  Token t = advanceToken();
  
  switch(t.type) {
    
    case DRegister:
      *inst &= (~ZERO_D); 
      break;
    case ARegister:
      *inst &= (~ZERO_A);
      break;
    case Memory:
      *inst = (*inst & ~ZERO_A) | USE_MEMORY;
      break;
    case Minus:
      *inst |= ADD_VALUES;
      break;
    case Plus:
      *inst |= ADD_VALUES;
      break;
    case Not:
      *inst |= NEGATE_OUT;
      break;
    case Or:
      *inst |= NEGATE_A;
      *inst |= NEGATE_D;
      *inst |= NEGATE_OUT;
      break;
    case And:
      // check for next value must be either M or A
      break;
    default:
      break;
  }

  return SUCCESS;
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
int match(int *symbols, size_t size) {
  Token current = getCurrent();
  for (size_t i = 0; i < size; i++) {
    if (current.type == symbols[i]) {
      return 1;
    }
  }

  return 0;
}
int peekMatch(int *symbols, size_t size) {
  Token current = peekToken();
  for (size_t i = 0; i < size; i++) {
    if (current.type == symbols[i]) {
      return 1;
    }
  }

  return 0;
}


Token getCurrent() {
  Token value;
  getValue(&value, parser.index-1, &parser.tokens);
  return value;
}
