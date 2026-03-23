#include "parser.h" 
#include "assembler.h"
#include "dynamicArray.h"
#define TARGET_NOT_FOUND -1

static Parser parser;


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

Array* parse() {
  
  Token t = advanceToken();
  Instruction current = CMD_BASE;
  // detination operation source, semicolon, branch  
  //while not newline
  while(!isAtEndToken()) { 
  switch(t.type) {
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
        addValue(&current,&parser.instructions);
        current = CMD_BASE;
      break;
 default:
      break;
    
    
  }
    t = advanceToken();
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
Token t;
  static int targetVals[] ={DRegister,ARegister,Memory,Not,Minus}; 
  if(!match(targetVals,sizeof(targetVals))) {
    jmp(inst);
  }
  int status = getTarget(inst,&t);    // operate 
  if(status == TARGET_NOT_FOUND) {
    
  }
  
}
int source(Instruction* inst);
int jmp(Instruction* inst);
int computation(Instruction* inst);

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

