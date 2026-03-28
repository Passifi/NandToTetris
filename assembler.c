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
  scanner.lineNumber = 0; 
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
      Token t = {"A",ARegister,scanner.lineNumber};
      addValue(&t,&tokens);
      break;
    }
    case 'D': {
       Token t = {"D",DRegister,scanner.lineNumber};
        addValue(&t,&tokens);
        break;
    }
    case 'M': {
      Token t = {"M",Memory,scanner.lineNumber};
      addValue(&t,&tokens);
      break;
    }

    case ';': {
      Token t = {";",Semicolon,scanner.lineNumber};
      addValue(&t,&tokens);
      break;
    }

    case '=': {
      Token t = {"=",Assign,scanner.lineNumber};
      addValue(&t,&tokens);
      break;
    }

    case '+': {
      Token t = {"+",Plus,scanner.lineNumber};
      addValue(&t,&tokens);
      break;
    }

    case '-': {
      Token t = {"-",Minus,scanner.lineNumber};
      addValue(&t,&tokens);
      break;
    }

    case '@': {
      Token t = {"@",SetAddress,scanner.lineNumber};
      addValue(&t,&tokens);
      break;
    }

    case '!': {
      Token t = {"!",Not,scanner.lineNumber};
      addValue(&t,&tokens);
      break;
    }
    case '&': {
      Token t = {"&",And,scanner.lineNumber};
      addValue(&t,&tokens);
      break;
    }
    case '|': {
      Token t = {"|",Or,scanner.lineNumber};
      addValue(&t,&tokens);
      break;
    }
   case 'J': {
      scanner.start = scanner.position;
      if (peek() == 'G') {
        advance();
        if (peek() == 'E') {
       Token t = {"JGE",JGE,scanner.lineNumber};
      addValue(&t,&tokens);
          advance();
        } else if (peek() == 'T') {
       Token t = {"JGT",JGT,scanner.lineNumber};
      addValue(&t,&tokens);
          advance();
        }
      } else if (peek() == 'L') {
        advance();
        if (peek() == 'E') {
       Token t = {"JLE",JLE,scanner.lineNumber};
      addValue(&t,&tokens);
          advance();
        } else if (peek() == 'T') {
       Token t = {"JLT",JLT,scanner.lineNumber};
      addValue(&t,&tokens);
          advance();
        }
      } else if (peek() == 'E') {
        advance();
        if (peek() == 'Q') {
       Token t = {"JEQ",JEQ,scanner.lineNumber};
      addValue(&t,&tokens);
          advance();
        }
      } else if (peek() == 'N') {
        advance();
        if (peek() == 'E') {
       Token t = {"JNE",JNE};
      addValue(&t,&tokens);
          advance();
        }

      } else {
        // identifier
      }
      break;
    }
    case '\n':
       Token t = {"\n",Newline,scanner.lineNumber};
      scanner.lineNumber++;
      addValue(&t,&tokens);
      break;
      case '1': {
        if(!isdigit(peek()))
        {
          Token t = {"1",One,scanner.lineNumber,1};
          addValue(&t,&tokens);
          break;
        }
      }

      case '0': {
        if(!isdigit(peek())) {
          Token t = {"0",Zero,scanner.lineNumber,1};
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
          Token t = {"number",Number,scanner.lineNumber,a};
          addValue(&t,&tokens);
      } else {
        // string
      }
    }
  }
  return &tokens;
}
