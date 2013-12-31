%option yylineno
%option noyywrap
%option yyclass="parser::PTXLexer"
%option prefix="ptx"
%option c++

%{
#include "PTXLexer.h"
#include <cassert>
#include <sstream>
#include <cstring>
%}

COMMENT ("//"[^\n]*)
TAB [\t]*

%%
{COMMENT}       {nextColumn += strlen(yytext); /* lCppComment(&yylloc); */ }
".version"      { return TOKEN_VERSION; }
".target"       { return TOKEN_TARGET; }
".address_size" { return TOKEN_ADDRESS_SIZE; }
".func"         { return TOKEN_FUNC; }
".entry"        { return TOKEN_ENTRY; }
".align"        { return TOKEN_ALIGN; }
".visible"      { return TOKEN_VISIBLE; }
".param"        { return TOKEN_PARAM; }
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
"["             { return '[';}
"]"             { return ']';}
"{"             { return '{';}
"}"             { return '}';}
"("             { return '(';}
")"             { return ')';}
";"             { return ';';}
","             { return ',';}
[0-9]+\.[0-9]+ { yylval->fvalue = atof(yytext); return TOKEN_FLOAT; }
[0-9]+   { yylval->ivalue = atoi(yytext); return TOKEN_INT; }
[a-zA-Z0-9_]+   { strcpy(yylval->svalue, yytext); return TOKEN_STRING;}
\n {
 //   yylloc.last_line++;
//    yylloc.last_column = 1;
    nextColumn = 1;
}
.              ;
%%

/** Handle a C++-style comment--eat everything up until the end of the line.
 */
#if 0
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
#endif
