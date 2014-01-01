#pragma once

#undef yyFlexLexer
#define yyFlexLexer ptxFlexLexer
#include <FlexLexer.h>


#include "PTXLexer.h"

#include <vector>
#include <sstream>
#include <string>
namespace ptx
{ 
	extern int yyparse( parser::PTXLexer&, parser::PTXParser& );
}

namespace parser
{
  /*! \brief An implementation of the Parser interface for PTX */
  class PTXParser 
  {
    typedef int token_t;
    std::ostream &out;
    std::string _identifier;
    token_t _dataTypeId;

    typedef std::pair<token_t, std::string> argument_t;
    std::vector<argument_t> argumentList, returnArgumentList;

    public:
    PTXParser(std::ostream &_out) : out(_out)
    {
    }

#define LOC YYLTYPE& location

    void identifier(const std::string &s) { _identifier = s;     }
    void dataTypeId(const token_t token)  { _dataTypeId = token; }
    void argumentDeclaration(LOC) 
    {
      argumentList.push_back(std::make_pair(_dataTypeId, _identifier));
    }

    std::string printArgument(const argument_t arg, const bool printDataType = true)
    {
      std::stringstream s;
      if (printDataType) 
        s << tokenToDataType(arg.first) << " ";
      s << arg.second << " ";
      return s.str();
    }

    std::string printArgumentList(const bool printDataType = true)
    {
      std::stringstream s;
      if (argumentList.empty()) return s.str();
      const int n = argumentList.size();
      s << " " << printArgument(argumentList[0], printDataType);
      for (int i = 1; i < n; i++)
        s << ",\n " <<  printArgument(argumentList[i], printDataType);
      return s.str();
    }

    void visibleEntryDeclaration(const std::string &calleeName, LOC) 
    {
      std::stringstream s;
      s << "extern \"C\" __global__ void \n";
      s << calleeName << " (\n";
      s << printArgumentList();
      s << "\n ) { asm(\" // entry \"); }\n\n";
      argumentList.clear();

      std::cerr << s.str();
    }

#undef LOC

    std::string tokenToDataType( token_t token )
    {
      switch( token )
      {
        case TOKEN_U8:   return "u8 "; break;
        case TOKEN_U16:  return "u16 "; break;
        case TOKEN_U32:  return "u32 "; break;
        case TOKEN_U64:  return "u64 "; break;
        case TOKEN_S8:   return "s8 "; break;
        case TOKEN_S16:  return "s16 "; break;
        case TOKEN_S32:  return "s32 "; break;
        case TOKEN_S64:  return "s64 "; break;
        case TOKEN_B8:   return "b8 "; break;
        case TOKEN_B16:  return "b16 "; break;
        case TOKEN_B32:  return "b32 "; break;
        case TOKEN_B64:  return "b64 "; break;
        case TOKEN_F32:  return "f32 "; break;
        case TOKEN_F64:  return "f64 "; break;
        default: std::cerr << "token= " << token<< std::endl; assert(0);
      }

      return "";
    }
  };
}


