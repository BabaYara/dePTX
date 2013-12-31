%locations

%code requires {

#define SourcePos YYLTYPE 

}

%{
#include <cstdio>
#include <iostream>
using namespace std;



#include "parse.tab.h"  // to get the token types that we return

// stuff from flex that bison needs to know about:
extern "C" int yylex();
//extern "C" int yyparse();
extern "C" FILE *yyin;
extern int line_num;
 
void yyerror(const char *s);
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
	int ival;
	float fval;
	char *sval;
}

// define the constant-string tokens:
%token TOKEN_VERSION TOKEN_TARGET TOKEN_ADDRESS_SIZE;
%token TOKEN_EXTERN TOKEN_FUNC TOKEN_ENTRY TOKEN_WEAK;
%token TOKEN_GLOBAL TOKEN_ALIGN
%token TOKEN_VISIBLE 
%token TOKEN_PARAM TOKEN_REG
%token TOKEN_B8 TOKEN_B16 TOKEN_B32 TOKEN_B64
%token TOKEN_U8 TOKEN_U16 TOKEN_U32 TOKEN_U64
%token TOKEN_S8 TOKEN_S16 TOKEN_S32 TOKEN_S64
%token TOKEN_F32 TOKEN_F64
%token TOKEN_PRED
%token ENDL

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%%
// the first rule defined is the highest-level rule, which in our
// case is just the concept of a whole "snazzle file":
ptxsource:
  header ptxbody 

header:
  ENDLS version target address_size { std:cerr << "Done reading PTX " << std::endl; }
version:
  TOKEN_VERSION FLOAT ENDL { std::cerr << "Reading PTX version " << $2  << std::endl; };
target:
  TOKEN_TARGET STRING ENDL { std::cerr << "Target " << $2  << std::endl; };
address_size:
  TOKEN_ADDRESS_SIZE INT ENDL { std::cerr << "Address_Size " << $2  << std::endl; };

 

anytoken: 
 TOKEN_VERSION | TOKEN_TARGET | TOKEN_ADDRESS_SIZE
| TOKEN_GLOBAL | TOKEN_ALIGN
| TOKEN_PARAM | TOKEN_REG
| TOKEN_B8 | TOKEN_B16 | TOKEN_B32 | TOKEN_B64
| TOKEN_U8 | TOKEN_U16 | TOKEN_U32 | TOKEN_U64
| TOKEN_S8 | TOKEN_S16 | TOKEN_S32 | TOKEN_S64
| TOKEN_F32 | TOKEN_F64
| TOKEN_PRED | STRING | FLOAT | INT | ENDL
| '<'
| '>'
| '%'
| '['
| ']'
| '{'
| '}'
| '('
| ')'
| ';';


ptxbody: 
  ptxbody anytoken
  | anytoken
  | ptxbody TOKEN_EXTERN TOKEN_FUNC 
  | ptxbody TOKEN_WEAK TOKEN_FUNC  
  | ptxbody TOKEN_EXTERN TOKEN_ENTRY  
  | ptxbody TOKEN_WEAK TOKEN_ENTRY  
  | ptxbody visibleFunctionDeclaration
  | ptxbody visibleEntryDeclaration

visibleEntryDeclaration: TOKEN_VISIBLE TOKEN_ENTRY STRING '('
{
   std::cerr << " __global__ " << $3 << std::endl;
}

visibleFunctionDeclaration: TOKEN_VISIBLE TOKEN_FUNC STRING '('
{
   std::cerr << " __device__ " << $3 << std::endl;
}


ENDLS:
	ENDLS ENDL
	| ENDL ;
%%

void yyerror(const char *s) {
	cout << "EEK, parse error on line " << line_num << "!  Message: " << s << endl;
	// might as well halt now:
	exit(-1);
}
