#include <cstdio>
#include <iostream>
#include <fstream>
#include <cassert>
#include "PTXParser.h"

int main() {
	// open a file handle to a particular file:
  std::istream & input = std::cin;
  std::ostream & output = std::cout;
  parser::PTXLexer lexer(&input, &output);
  parser::PTXParser state;

	// parse through the input until there is no more:
  //

  do {
    ptx::yyparse(lexer, state);
  }
  while (!input.eof());
	
}
