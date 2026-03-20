#include "assembler.h"
#include <ctype.h>
static Scanner scanner;

Array tokens;
static int currentToken = 0;
void initializeScanner(char *data,size_t size) {
  scanner.data = data;
  scanner.position = 0;
  scanner.start = 0;
  scanner.size = size;
  initializeArray(&tokens, sizeof(Token));

}

char advance() { return scanner.data[scanner.position++]; }
char peek() { return scanner.data[scanner.position]; }
int isAtEnd() { return scanner.position == scanner.size; }
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
      Token t = {"M",Memory};
      addValue(&t,&tokens);
      break;
    }

    case ';': {
      Token t = {";",Semicolon};
      addValue(&t,&tokens);
      break;
    }

    case '=': {
      Token t = {"=",Assign};
      addValue(&t,&tokens);
      break;
    }

    case '+': {
      Token t = {"+",Plus};
      addValue(&t,&tokens);
      break;
    }

    case '-': {
      Token t = {"-",Minus};
      addValue(&t,&tokens);
      break;
    }

    case '@': {
      Token t = {"@",SetAddress};
      addValue(&t,&tokens);
      break;
    }

    case '!': {
      Token t = {"!",Not};
      addValue(&t,&tokens);
      break;
    }
    case '&': {
      Token t = {"&",And};
      addValue(&t,&tokens);
      break;
    }
    case '|': {
      Token t = {"|",Or};
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
       Token t = {"\n",Newline};
      addValue(&t,&tokens);
      break;
      case '1': {
        if(!isdigit(peek()))
        {

          Token t = {"1",Number,1};
          addValue(&t,&tokens);
          break;
  
        }

      }
 
    default:
      if (isdigit(c)) {
          unsigned int a = 0; 
          scanner.start = scanner.position;
          a += c - '0'; 
          advance(); 
          while(isdigit(peek())) {
            a *= 10;
            a += c - '0';
            advance();
          }
          Token t = {"number",Number,a};
          addValue(&t,&tokens);
      } else {
        // string
      }
    }
  }
  return &tokens;
}
