%{
#include <iostream>
using namespace std;
#include "parse.tab.h"
#define YY_DECL extern "C" int yylex()
static void lCppComment(SourcePos *);
int line_num = 1;
%}

WHITESPACE [ \t\r]+
INT_NUMBER (([0-9]+)|(0x[0-9a-fA-F]+)|(0b[01]+))[uUlL]*[kMG]?[uUlL]*
INT_NUMBER_DOTDOTDOT (([0-9]+)|(0x[0-9a-fA-F]+)|(0b[01]+))[uUlL]*[kMG]?[uUlL]*\.\.\.
FLOAT_NUMBER (([0-9]+|(([0-9]+\.[0-9]*[fF]?)|(\.[0-9]+)))([eE][-+]?[0-9]+)?[fF]?)
HEX_FLOAT_NUMBER (0x[01](\.[0-9a-fA-F]*)?p[-+]?[0-9]+[fF]?)
FORTRAN_DOUBLE_NUMBER (([0-9]+\.[0-9]*[dD])|([0-9]+\.[0-9]*[dD][-+]?[0-9]+)|([0-9]+[dD][-+]?[0-9]+)|(\.[0-9]*[dD][-+]?[0-9]+))

IDENT [a-zA-Z_][a-zA-Z_0-9]*
ZO_SWIZZLE ([01]+[w-z]+)+|([01]+[rgba]+)+|([01]+[uv]+)+

%%
"//"            { line_num++; lCppComment(&yylloc); }
[ \t]          ;
".version"      { return TOKEN_VERSION; }
".target"       { return TOKEN_TARGET; }
".address_size" { return TOKEN_ADDRESS_SIZE; }
".extern"       { return TOKEN_EXTERN;}
".weak"       { return TOKEN_WEAK;}
".func"         { return TOKEN_FUNC; }
".entry"        { return TOKEN_ENTRY; }
".global"       { return TOKEN_GLOBAL; }
".align"        { return TOKEN_ALIGN; }
".visible"      { return TOKEN_VISIBLE; }
".param"        { return TOKEN_PARAM; }
".reg"          { return TOKEN_REG; }
".b8"           { return TOKEN_B8;}
".b16"          { return TOKEN_B16;}
".b32"          { return TOKEN_B32;}
".b64"          { return TOKEN_B64;}
".u8"           { return TOKEN_U8;}
".u16"          { return TOKEN_U16;}
".u32"          { return TOKEN_U32;}
".u64"          { return TOKEN_U64;}
".s8"           { return TOKEN_S8;}
".s16"          { return TOKEN_S16;}
".s32"          { return TOKEN_S32;}
".s64"          { return TOKEN_S64;}
".f32"          { return TOKEN_F32;}
".f64"          { return TOKEN_F64;}
".pred"         { return TOKEN_PRED;}
"<"             { return '<';}
">"             { return '>';}
"%"             { return '%';}
"["             { return '[';}
"]"             { return ']';}
"{"             { return '{';}
"}"             { return '}';}
"("             { return '(';}
")"             { return ')';}
";"             { return ';';}
[0-9]+\.[0-9]+ { yylval.fval = atof(yytext); return FLOAT; }
[0-9]+   { yylval.ival = atoi(yytext); return INT; }
[a-zA-Z0-9_]+   {
	yylval.sval = strdup(yytext);
	return STRING;
}
\n             { ++line_num; return ENDL; }
.              ;
%%

/** Handle a C++-style comment--eat everything up until the end of the line.
 */
static void
lCppComment(SourcePos *pos) {
    char c;
    do {
        c = yyinput();
    } while (c != 0 && c != '\n');
    if (c == '\n') {
        pos->last_line++;
        pos->last_column = 1;
    }
}
