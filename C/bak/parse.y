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
%token TOKEN_VERSION TOKEN_TARGET TOKEN_ADDRESS_SIZE
%token TOKEN_VISIBLE TOKEN_FUNC TOKEN_ENTRY
%token TOKEN_PARAM TOKEN_ALIGN 
%token TOKEN_B8 TOKEN_B16 TOKEN_B32 TOKEN_B64
%token TOKEN_U8 TOKEN_U16 TOKEN_U32 TOKEN_U64
%token TOKEN_S8 TOKEN_S16 TOKEN_S32 TOKEN_S64
%token TOKEN_F32 TOKEN_F64

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%type<sval> identifier
%type<ival> arrayDimensionSet
%type<ival> alignment

%%
// the first rule defined is the highest-level rule, which in our
// case is just the concept of a whole "snazzle file":
ptxsource:
  header ptxbody;

header:
  version target  address_size { std:cerr << "Done reading PTX " << std::endl; }
version:
  TOKEN_VERSION FLOAT  { std::cerr << "Reading PTX version " << $2  << std::endl; };
target:
  TOKEN_TARGET STRING  { std::cerr << "Target " << $2  << std::endl; };
address_size:
  TOKEN_ADDRESS_SIZE INT  { std::cerr << "Address_Size " << $2  << std::endl; };

 

dataTypeId : TOKEN_U8 | TOKEN_U16 | TOKEN_U32 | TOKEN_U64 | TOKEN_S8 
	| TOKEN_S16 | TOKEN_S32 | TOKEN_S64 | TOKEN_B8 | TOKEN_B16 | TOKEN_B32 
	| TOKEN_B64 | TOKEN_F32 | TOKEN_F64;

anytoken: 
  TOKEN_ALIGN 
| TOKEN_PARAM 
| dataTypeId
| STRING | FLOAT | INT
| TOKEN_FUNC | TOKEN_ENTRY
| '['
| ']'
| '{'
| '}'
| '('
| ')'
| ';'
| ',';


ptxbody: 
    ptxbody visibleFunctionDeclaration | visibleFunctionDeclaration
  | ptxbody visibleEntryDeclaration| visibleEntryDeclaration
  | ptxbody anytoken | anytoken;

arrayDimensionSet : '[' INT ']' { $$ = $2; }
// arrayDimensionSet : arrayDimensionSet '[' INT ']' { $$ = $2; }
// arrayDimensionSet : '[' ']' { $$ = 0; }
arrayDimensions : /* empty string */;
arrayDimensions : arrayDimensionSet;

identifier: STRING { $$ = $1; /* kiss-my-ass */};
parameter : TOKEN_PARAM;

alignment : TOKEN_ALIGN INT {$$ = $2;}
addressableVariablePrefix : dataTypeId;
addressableVariablePrefix : alignment dataTypeId;

argumentDeclaration : parameter addressableVariablePrefix identifier arrayDimensions;


argumentListBegin : '(';
argumentListEnd : ')';
argumentListBody : argumentDeclaration;
argumentListBody : /* empty string */;
argumentListBody : argumentListBody ',' argumentDeclaration;
argumentList: argumentListBegin argumentListBody argumentListEnd;

visibleEntryDeclaration: TOKEN_VISIBLE TOKEN_ENTRY identifier argumentList
{
   std::cerr << " __global__ " << $3 << std::endl;
};

visibleFunctionDeclaration: TOKEN_VISIBLE TOKEN_FUNC STRING '('
{
   std::cerr << " __device__ " << $3 << std::endl;
}


%%

void yyerror(const char *s) {
	cout << "EEK, parse error on line " << line_num << "!  Message: " << s << endl;
	// might as well halt now:
	exit(-1);
}
