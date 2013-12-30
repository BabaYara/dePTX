/*! \file PTXParser.cpp
	\date Monday January 19, 2009
	\author Gregory Diamos <gregory.diamos@gatech.edu>
	\brief The source file for the PTXParser class.
*/

#ifndef PTX_PARSER_CPP_INCLUDED
#define PTX_PARSER_CPP_INCLUDED

// Ocelot Includes
#include "PTXParser.h"
#include <cassert>

namespace parser
{
  PTXParser::PTXParser(std::ostream &_out) : out(_out)
  {
    isArgumentList        = false;
    isReturnArgumentList  = false;
  }
  void PTXParser::version( double version, YYLTYPE& location )
  {
    out << "_PTX_Version(" << version << ")" << std::endl;
  };
  void PTXParser::argumentDeclaration( const std::string& name, YYLTYPE& location )
  {
    out << " " << name.c_str();
    if (isArgumentList)
      out  << std::endl;
  }
  void PTXParser::argumentListBegin( YYLTYPE& location ) 
  {
    isArgumentList = true;
    out << "(\n";
  }
  void PTXParser::argumentListEnd( YYLTYPE& location )
  {
    isArgumentList = false;
    out << ");\n";
  }

  /********** FUNC *********/
  
  void PTXParser::functionBegin( YYLTYPE& location )
  {
  }
  void PTXParser::functionName( const std::string& name, YYLTYPE& location )
  {
    out << "__function " << name.c_str();
  }
  void PTXParser::functionDeclaration( YYLTYPE& location, bool body )
  {
  }

  void PTXParser::openBrace( YYLTYPE& location )
  {
//    out << "{";
  }
  void PTXParser::closeBrace( YYLTYPE& location )
  {
 //   out << "};\n";
  }
  void PTXParser::returnArgumentListBegin( YYLTYPE& location )
  {
    isReturnArgumentList = true;
    out << "( ";
  }
  void PTXParser::returnArgumentListEnd( YYLTYPE& location )
  {
    isReturnArgumentList = false;
    out << " ) ";
  }

  /********** ENTRY *********/

  void PTXParser::entry( const std::string& name, YYLTYPE& location )
  {
    out << "__kernel " << name.c_str();
  }
  void PTXParser::entryDeclaration( YYLTYPE& location ) 
  {
  }
  void PTXParser::entryPrototype( YYLTYPE& location )
  {
  }
  void PTXParser::entryStatement( YYLTYPE& location )
  {
  }
  void PTXParser::metadata( const std::string& comment )
  {
  }

  void PTXParser::attribute( bool visible, bool external, bool weak )
  {
    if (visible)
      out << "__visible ";
    else if (external)
      out << "__extern ";
    else if (weak)
      out << "__weak ";
  }

  void PTXParser::dataType( int token )
  {
    if (isArgumentList || isReturnArgumentList)
      out << " " << tokenToDataType(token).c_str() << " ";
  }
  void PTXParser::addressSpace( int token )
  {
  }


  /****************/

  std::string PTXParser::tokenToDataType( int token )
  {
    switch( token )
    {
      case TOKEN_U8:   return "_u8"; break;
      case TOKEN_U16:  return "_u16"; break;
      case TOKEN_U32:  return "_u32"; break;
      case TOKEN_U64:  return "_u64"; break;
      case TOKEN_S8:   return "_s8"; break;
      case TOKEN_S16:  return "_s16"; break;
      case TOKEN_S32:  return "_s32"; break;
      case TOKEN_S64:  return "_s64"; break;
      case TOKEN_B8:   return "_b8"; break;
      case TOKEN_B16:  return "_b16"; break;
      case TOKEN_B32:  return "_b32"; break;
      case TOKEN_B64:  return "_b64"; break;
      case TOKEN_PRED: return "_pred"; break;
      case TOKEN_F16:  return "_f16"; break;
      case TOKEN_F32:  return "_f32"; break;
      case TOKEN_F64:  return "_f64"; break;
      default: assert(0);
    }

    return "";
  }

}

#endif

