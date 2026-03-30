#include "parser.h"
#include "assembler.h"
#include "dynamicArray.h"
#define TARGET_NOT_FOUND -1
#define SUCCESS 0 
#define PARSING_ERROR -12
static Parser parser;
static unsigned int line;
static int computationVals[] ={Not,Plus,Minus,Or,And}; 
void initializeParser(Array tokens) {
  parser.tokens = tokens;
  initializeArray(&parser.instructions, sizeof(Instruction));
}

int isAtEndToken() { return parser.tokens.index <= parser.index; }

Token advanceToken() {
  Token t;
  getValue(&t, parser.index++, &parser.tokens);
  return t;
}

Token getLast() {
  Token t; 
  getValue(&t,parser.index-2,&parser.tokens);
  return t;
}

Token peekToken() {
   Token t;
  getValue(&t,parser.index,&parser.tokens);
  return t;

}

Array* parse() {

  Instruction inst = CMD_BASE;
  while(target(&inst) != PARSING_ERROR && !isAtEndToken()) {
    
    addValue(&inst, &parser.instructions); 
    inst = CMD_BASE; 
  }
  
  return &parser.instructions;
}
int target(Instruction* inst) {
  Token t = advanceToken();
  if(t.type == Newline) {
    t = advanceToken();
  }
  printf("%s\n",t.literal);
  static int targetVals[] ={DRegister,ARegister,Memory}; 
  int result = 0; 
  int foundTarget = 0; 
  if(match(computationVals,5)) {
    return computation(inst);
  }
  while(match(targetVals,3)) {
    printf("Target Value found\n");
    if(peekToken().type == Semicolon) {
      if(foundTarget>1) {
        printf("1.Expected = after destination\n Error in Line: %d\n",t.line);
         
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
int registerOperand(Instruction *inst) {
  Token t = advanceToken();
  switch(t.type) {      
    case One: {

      break; 
      }
    case DRegister:
      *inst |= NEGATE_A | NEGATE_OUT;
      break;
    case Memory:
      *inst |= USE_MEMORY;
    case ARegister: 
      *inst |= NEGATE_D | NEGATE_OUT;
      break;
    default:
      return PARSING_ERROR;
  }
  return SUCCESS;
}   
int operator(Instruction *inst) {
  Token t = advanceToken();
  switch(t.type) {
    case Minus: {
      *inst |= ADD_VALUES | NEGATE_OUT ;
      if((*inst & ZERO_D) != 0) {
        *inst |= NEGATE_A; 
        
      } 
      
      Token nextToken = peekToken();
      return registerOperand(inst);
      break;
    }
    case Plus: {
      *inst |= ADD_VALUES;
      Token nextToken = peekToken(); 
      if(nextToken.type == Memory) {
        *inst |= USE_MEMORY;
      }
      else if(nextToken.type == One) {
         Instruction buffer = 0b0000111111000000;
        buffer ^= *inst; 
        *inst = buffer;
      }
        
        advanceToken(); 
      }
    break;
    case Or:
      *inst |= NEGATE_A | NEGATE_D | NEGATE_OUT;
       if(peekToken().type == Memory) {
        *inst |= USE_MEMORY;
      }  

        advanceToken(); 
    break;
    case And:
      *inst &= 0b1111000000111111;
      if(peekToken().type == Memory) {
        *inst |= USE_MEMORY;
      }

        advanceToken(); 
    break;
    default:  
      printf("Expected operator after Register/Memory declaration in computation [+-|&]\n");
      printf("Token Value: %s\n",t.literal); 
      return PARSING_ERROR;
  }
  return SUCCESS;
}
int computation(Instruction* inst) {
  printf("Jumped into computation\n");
  Token t = advanceToken();
  printf("Token Value: %s\n",t.literal); 
  switch(t.type) {
    
    case DRegister:
      *inst |= (ZERO_A) | NEGATE_A; 
      if(peekToken().type == Semicolon) {
          return jmp(inst);
      }
      return operator(inst);
      break;
    case ARegister:
      *inst |= (ZERO_D) | NEGATE_D;
      return operator(inst);
      break;
    case Memory:
      *inst |= (ZERO_D) | NEGATE_D | USE_MEMORY;
      return operator(inst);
      break;
    case Not:
      *inst |= NEGATE_OUT;
      break;
    default:
      break;
  }

  return SUCCESS;
}


int jmp(Instruction *inst) {
  return 0;
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
