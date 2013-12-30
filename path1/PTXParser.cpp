/*! \file PTXParser.cpp
	\date Monday January 19, 2009
	\author Gregory Diamos <gregory.diamos@gatech.edu>
	\brief The source file for the PTXParser class.
*/

#ifndef PTX_PARSER_CPP_INCLUDED
#define PTX_PARSER_CPP_INCLUDED

// Ocelot Includes
#include "PTXParser.h"

namespace parser
{
  void PTXParser::version( double version, YYLTYPE& location )
  {
    out << "_PTX_Version(" << version << ")" << std::endl;
  };
  void PTXParser::argumentDeclaration( const std::string& name, YYLTYPE& location )
  {
    out << "\t" << name.c_str() << std::endl;
  }
  void PTXParser::argumentListBegin( YYLTYPE& location ) 
  {
    out << "(\n";
  }
  void PTXParser::argumentListEnd( YYLTYPE& location )
  {
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
    out << "{\n";
  }
  void PTXParser::closeBrace( YYLTYPE& location )
  {
    out << ");\n";
  }
  void PTXParser::returnArgumentListBegin( YYLTYPE& location )
  {
    out << "((\n";
  }
  void PTXParser::returnArgumentListEnd( YYLTYPE& location )
  {
    out << "))\n";
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
}

#endif

