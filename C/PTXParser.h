#pragma once

#undef yyFlexLexer
#define yyFlexLexer ptxFlexLexer
#include <FlexLexer.h>


#include "PTXLexer.h"

#include <vector>
namespace ptx
{ 
	extern int yyparse( parser::PTXLexer&, parser::PTXParser& );
}

namespace parser
{
  /*! \brief An implementation of the Parser interface for PTX */
  class PTXParser 
  {
    std::ostream &out;
    public:
    PTXParser(std::ostream &_out) : out(_out)
    {
    }

    void visibleEntryDeclaration(std::string name, YYLTYPE& location)
    {
    }
  };
}


