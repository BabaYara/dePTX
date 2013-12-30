#include <cstdio>
#include <iostream>
#include <fstream>
#include "PTXParser.h"

namespace ptx
{
  int yyparse (parser::PTXLexer& lexer, parser::PTXParser& state);
}

int main() {
	// open a file handle to a particular file:
  std::istream & input = std::cin;
  std::ostream & output = std::cout;
  parser::PTXLexer lexer(&input, &output);
  parser::PTXParser state;

	// parse through the input until there is no more:
  //

  ptx::yyparse(lexer, state);

#if 0
	do {
		yyparse();
	} while (!feof(yyin));
#endif
	
}
