#include <cstdio>
#include <iostream>
#include "ptxgrammar.hh"
extern "C" FILE *yyin;

int main() {
	// open a file handle to a particular file:
	FILE *myfile = fopen("kernel.ptx", "r");
	// make sure it's valid:
	if (!myfile) {
    std::cout << "I can't open a.snazzle.file!" << std::endl;
		return -1;
	}
	// set lex to read from it instead of defaulting to STDIN:
	yyin = myfile;

	// parse through the input until there is no more:
  
  parser::PTXLexer lexer;
  parse::PTXParser::State state;
	
	do {
		yyparse();
	} while (!feof(yyin));
	
}
