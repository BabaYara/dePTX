#include <cstdio>
using namespace std;
#include <iostream>
#include "parse.tab.h"
extern "C" FILE *yyin;

int main() {
	// open a file handle to a particular file:
	FILE *myfile = fopen("in.snazzle", "r");
	// make sure it's valid:
	if (!myfile) {
		cout << "I can't open a.snazzle.file!" << endl;
		return -1;
	}
	// set lex to read from it instead of defaulting to STDIN:
	yyin = myfile;

	// parse through the input until there is no more:
	
	do {
		yyparse();
	} while (!feof(yyin));
	
}
