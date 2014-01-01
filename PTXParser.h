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
    private:
    typedef int token_t;
    std::ostream &out;
    std::string _identifier;
    token_t _dataTypeId;
    int _alignment;

    bool isArgumentList, isReturnArgumentList;
    typedef std::pair<token_t, std::string> argument_t;
    std::vector<argument_t> argumentList, returnArgumentList;
    std::vector<int> arrayDimensionsList;

    public:
    PTXParser(std::ostream &_out) : out(_out)
    {
      isArgumentList = isReturnArgumentList = false;
    }

    void printHeader()
    {
      std::stringstream s;
      s << "typedef struct { unsigned char _v[1]; }      b8_t; \n";
      s << "typedef struct { unsigned short _v[1]; }    b16_t; \n";
      s << "typedef struct { unsigned char _v[1]; }      u8_t; \n";
      s << "typedef struct { unsigned short _v[1]; }    u16_t; \n";
      s << "typedef struct {          char _v[1]; }      s8_t; \n";
      s << "typedef struct {          short _v[1]; }    s16_t; \n";
      s << "typedef unsigned int       b32_t; \n";
      s << "typedef unsigned long long b64_t; \n";
      s << "typedef unsigned int       u32_t; \n";
      s << "typedef unsigned long long u64_t; \n";
      s << "typedef int                s32_t; \n";
      s << "typedef long long          s64_t; \n";
      s << "typedef float              f32_t; \n";
      s << "typedef double             f64_t; \n";
      s << " \n";
      std::cout << s.str();
    }

#define LOC YYLTYPE& location

    void identifier(const std::string &s) { _identifier = s;     }
    void dataTypeId(const token_t token)  { _dataTypeId = token; }
    void argumentListBegin(LOC) { isArgumentList = true;  }
    void argumentListEnd  (LOC) { isArgumentList = false; }
    void returnArgumentListBegin(LOC) { isReturnArgumentList = true;  }
    void returnArgumentListEnd  (LOC) { isReturnArgumentList = false; }
    void argumentDeclaration(LOC) 
    {
      assert(_alignment == 0 || _alignment == 1);
      if (isArgumentList)
        argumentList.push_back(std::make_pair(_dataTypeId, _identifier));
      else if (isReturnArgumentList)
        returnArgumentList.push_back(std::make_pair(_dataTypeId, _identifier));
      else
        assert(0);
    }
    void alignment(const int value) { _alignment = value; }

    void arrayDimensions(const int value)
    {
      arrayDimensionsList.push_back(value);
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
      assert(returnArgumentList.empty());
      s << "extern \"C\" \n";
      s << "__global__ void " << calleeName << " (\n";
      s << printArgumentList();
      s << "\n ) { asm(\" // entry \"); }\n";

     
      /* check if this is an "export"  entry */
      const int entryNameLength = calleeName.length();
      const int hostNameLength = std::max(entryNameLength-9,0);
      const std::string ___export(&calleeName.c_str()[hostNameLength]);
      if (___export.compare("___export") == 0)
      {
        std::string hostCalleeName;
        hostCalleeName.append(calleeName.c_str(), hostNameLength);
        s << "/*** host interface ***/\n";
        s << "extern \"C\" \n";
        s << "__host__ void " << hostCalleeName << " (\n";
        s << printArgumentList();
        s << "\n )\n";
        s << "{\n   ";
        s << calleeName;
        s << "<<<1,32>>>(\n";
        s << printArgumentList(false);
        s << ");\n";
        s << "}\n";
      }
      s << "\n";
      argumentList.clear();

      std::cout << s.str();
    }
    
    void visibleFunctionDeclaration(const std::string &calleeName, LOC) 
    {
      std::stringstream s;
      assert(returnArgumentList.size() < 2);
      s << "extern \"C\" \n";
      s << "__device__ ";
      if (returnArgumentList.empty())
        s << " void ";
      else
        s << " " <<  tokenToDataType(returnArgumentList[0].first);
      s << calleeName << " (\n";
      s << printArgumentList();

      if (returnArgumentList.empty())
        s << "\n ) { asm(\" // function \"); }\n\n";
      else
        s << "\n ) { asm(\" // function \"); return 0;} /* return value to disable warnings */\n\n";

      argumentList.clear();
      returnArgumentList.clear();

      std::cout << s.str();
    }

    void visibleInitializableDeclaration(const std::string &name, LOC)
    {
      assert(arrayDimensionsList.size() == 1);
      std::stringstream s;
      s << "extern \"C\" __device__ ";
      if (_alignment > 0)
        s << "__attribute__((aligned(" << _alignment << "))) ";
      s << tokenToDataType(_dataTypeId);
      s << name << "[" << arrayDimensionsList[0] << "] = {0};\n\n";
      std::cout << s.str();
    }

#undef LOC

    std::string tokenToDataType( token_t token )
    {
      switch( token )
      {
        case TOKEN_U8:   return "u8_t "; break;
        case TOKEN_U16:  return "u16_t "; break;
        case TOKEN_U32:  return "u32_t "; break;
        case TOKEN_U64:  return "u64_t "; break;
        case TOKEN_S8:   return "s8_t "; break;
        case TOKEN_S16:  return "s16_t "; break;
        case TOKEN_S32:  return "s32_t "; break;
        case TOKEN_S64:  return "s64_t "; break;
        case TOKEN_B8:   return "b8_t "; break;
        case TOKEN_B16:  return "b16_t "; break;
        case TOKEN_B32:  return "b32_t "; break;
        case TOKEN_B64:  return "b64_t "; break;
        case TOKEN_F32:  return "f32_t "; break;
        case TOKEN_F64:  return "f64_t "; break;
        default: std::cerr << "token= " << token<< std::endl; assert(0);
      }

      return "";
    }
  };
}


