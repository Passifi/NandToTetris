#include "assembler.h"
#include <ctype.h>

static Scanner scanner;

Token tokens[1024];
static int currentToken = 0;
void initializeScanner(char *data) {
  scanner.data = data;
  scanner.position = 0;
  scanner.start = 0;
}

char advance() { return scanner.data[scanner.position++]; }
char peek() { return scanner.data[scanner.position + 1]; }
int isAtEnd() { return scanner.position == 1024; }
void scan() {
  while (!isAtEnd()) {
    char c = advance();
    switch (c) {
    case 'A': {
      tokens[currentToken].type = ARegister;
      tokens[currentToken++].literal = "A";
      currentToken++;
      break;
    }
    case 'D': {
      tokens[currentToken].type = DRegister;
      tokens[currentToken++].literal = "D";
      break;
    }

    case 'M': {
      tokens[currentToken].type = Memory;
      tokens[currentToken++].literal = "M";
      break;
    }

    case ';': {
      tokens[currentToken].type = Semicolon;
      tokens[currentToken++].literal = ";";
      break;
    }

    case '=': {
      tokens[currentToken].type = Assign;
      tokens[currentToken++].literal = "=";
      break;
    }

    case '+': {
      tokens[currentToken].type = Plus;
      tokens[currentToken++].literal = "+";
      break;
    }

    case '-': {
      tokens[currentToken].type = Minus;
      tokens[currentToken++].literal = "-";
      break;
    }

    case '@': {
      tokens[currentToken].type = SetAddress;
      tokens[currentToken++].literal = "@";
      break;
    }

    case '!': {
      tokens[currentToken].type = Not;
      tokens[currentToken++].literal = "!";
      break;
    }

    case 'J': {
      scanner.start = scanner.position;
      if (peek() == 'G') {
        advance();
        if (peek() == 'E') {
          tokens[currentToken].type = JGE;
          tokens[currentToken++].literal = "JGE";
          advance();
        } else if (peek() == 'T') {
          tokens[currentToken].type = JGT;
          tokens[currentToken++].literal = "JGT";
          advance();
        }
      } else if (peek() == 'L') {
        advance();
        if (peek() == 'E') {
          tokens[currentToken].type = JLE;
          tokens[currentToken++].literal = "JGE";
          advance();
        } else if (peek() == 'T') {
          tokens[currentToken].type = JLT;
          tokens[currentToken++].literal = "JGT";
          advance();
        }

      } else if (peek() == 'E') {
        advance();
        if (peek() == 'Q') {
          tokens[currentToken].type = JEQ;
          tokens[currentToken++].literal = "JEQ";
          advance();
        }
      } else if (peek() == 'N') {
        advance();
        if (peek() == 'E') {
          tokens[currentToken].type = JNE;
          tokens[currentToken++].literal = "JNE";
          advance();
        }

      } else {
        // identifier
      }
      break;
    }
    case '\n':
      tokens[currentToken].type = Newline;
      tokens[currentToken++].literal = "Newline";
      break;
    default:
      if (isdigit(c)) {
        // number
      } else {
        // string
      }
    }
  }
}
