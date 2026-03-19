#include "assembler.h"
#include <ctype.h>
static Scanner scanner;

Array tokens;
static int currentToken = 0;
void initializeScanner(char *data) {
  scanner.data = data;
  scanner.position = 0;
  scanner.start = 0;
  initializeArray(&tokens, sizeof(Token));

}

char advance() { return scanner.data[scanner.position++]; }
char peek() { return scanner.data[scanner.position + 1]; }
int isAtEnd() { return scanner.position == 1024; }
Array* scan() {
  while (!isAtEnd()) {
    char c = advance();
    switch (c) {
    case 'A': {
      Token t = {"A",ARegister};
      addValue(&t,&tokens);
      break;
    }
    case 'D': {
       Token t = {"D",DRegister};
      addValue(&t,&tokens);
      
        break;
    }

    case 'M': {
       Token t = {"D",DRegister};
      addValue(&t,&tokens);
      break;
    }

    case ';': {
       Token t = {"D",DRegister};
      addValue(&t,&tokens);
      break;
    }

    case '=': {
       Token t = {"D",DRegister};
      addValue(&t,&tokens);
      break;
    }

    case '+': {
       Token t = {"D",DRegister};
      addValue(&t,&tokens);
      break;
    }

    case '-': {
       Token t = {"D",DRegister};
      addValue(&t,&tokens);
      break;
    }

    case '@': {
       Token t = {"D",DRegister};
      addValue(&t,&tokens);
      break;
    }

    case '!': {
       Token t = {"D",DRegister};
      addValue(&t,&tokens);
      break;
    }

    case 'J': {
      scanner.start = scanner.position;
      if (peek() == 'G') {
        advance();
        if (peek() == 'E') {
       Token t = {"D",DRegister};
      addValue(&t,&tokens);
          advance();
        } else if (peek() == 'T') {
       Token t = {"D",DRegister};
      addValue(&t,&tokens);
          advance();
        }
      } else if (peek() == 'L') {
        advance();
        if (peek() == 'E') {
       Token t = {"D",DRegister};
      addValue(&t,&tokens);
          advance();
        } else if (peek() == 'T') {
       Token t = {"D",DRegister};
      addValue(&t,&tokens);
          advance();
        }

      } else if (peek() == 'E') {
        advance();
        if (peek() == 'Q') {
       Token t = {"D",DRegister};
      addValue(&t,&tokens);
          advance();
        }
      } else if (peek() == 'N') {
        advance();
        if (peek() == 'E') {
       Token t = {"D",DRegister};
      addValue(&t,&tokens);
          advance();
        }

      } else {
        // identifier
      }
      break;
    }
    case '\n':
       Token t = {"D",DRegister};
      addValue(&t,&tokens);
      break;
    default:
      if (isdigit(c)) {
        // number
      } else {
        // string
      }
    }
  }
  return &tokens;
}
