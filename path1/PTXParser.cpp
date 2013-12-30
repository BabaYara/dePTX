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
    isInitializableDeclaration = false;
    isEntry = false;

    stmt_attribute = static_cast<attribute_t>(-1);
    stmt_locationAddress = static_cast<locationAddress_t>(-1);
  }
  void PTXParser::version( double version, YYLTYPE& location )
  {
    out << "_PTX_Version(" << version << ")" << std::endl;
  };
  void PTXParser::argumentDeclaration( const std::string& name, YYLTYPE& location )
  {
    if (isReturnArgumentList)
      returnArgumentList.push_back(std::make_pair(tokenDataType, name));
    if (isArgumentList)
      argumentList.push_back(std::make_pair(tokenDataType, name));
  }
  void PTXParser::argumentListBegin( YYLTYPE& location ) 
  {
    isArgumentList = true;
  }
  void PTXParser::argumentListEnd( YYLTYPE& location )
  {
    isArgumentList = false;
  }

  /********** FUNC *********/
  
  void PTXParser::functionBegin( YYLTYPE& location )
  {
    functionAttribute = stmt_attribute;
  }
  void PTXParser::functionName( const std::string& name, YYLTYPE& location )
  {
    calleeName = name;
  }
  void PTXParser::functionDeclaration( YYLTYPE& location, bool body )
  {
    assert(!isEntry);
    assert(returnArgumentList.size() <=1);
    out  
      << attributeString(functionAttribute);
    out << "extern \"C\" __device__ ";
    if (returnArgumentList.empty())
      out << "void ";
    else
      out << tokenToDataType(returnArgumentList[0].first);
    out << calleeName << " (\n " 
      << tokenToDataType(argumentList[0].first)
      << argumentList[0].second << " ";
    const int narg = argumentList.size();
    for (int i = 0; i < narg; i++)
      out << ",\n " << tokenToDataType(argumentList[0].first)
      << argumentList[i].second;
    out << "\n); \n";


    isEntry = false;
    returnArgumentList.clear();
    argumentList.clear();
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
  }
  void PTXParser::returnArgumentListEnd( YYLTYPE& location )
  {
    isReturnArgumentList = false;
  }

  /********** ENTRY *********/

  void PTXParser::entry( const std::string& name, YYLTYPE& location )
  {
    isEntry = true;
    calleeName = name;
  }
  void PTXParser::entryDeclaration( YYLTYPE& location ) 
  {
    assert(isEntry);
    assert(returnArgumentList.size() <=1);
    out  
      << attributeString(functionAttribute);
    out << "extern \"C\" __global ";
    assert (returnArgumentList.empty());
    out << "void ";
    out << calleeName << " (\n " 
      << tokenToDataType(argumentList[0].first)
      << argumentList[0].second << " ";
    const int narg = argumentList.size();
    for (int i = 0; i < narg; i++)
      out << ",\n " << tokenToDataType(argumentList[0].first)
      << argumentList[i].second;
    out << "\n); \n";


    isEntry = false;
    returnArgumentList.clear();
    argumentList.clear();
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
    assert( visible + external + weak < 2 );
    if (visible)
    {
//      out << "visible\n";
      stmt_attribute = VISIBLE;
    }
    else if (external)
    {
//      out << "extern\n";
      stmt_attribute = EXTERN;
    }
    else if (weak)
    {
//      out << "weak\n";
      stmt_attribute = WEAK;
    }
    else
    {
 //     out << "none\n";
      stmt_attribute = NONE;
    }
  }

  void PTXParser::dataType( int token )
  {
    tokenDataType = token;
  }
  void PTXParser::addressSpace( int token )
  {
  }
  void PTXParser::locationAddress( int token )
  {
    switch (token)
    {
      case TOKEN_PARAM:  stmt_locationAddress = PARAM;   break;
      case TOKEN_REG:    stmt_locationAddress = REG;     break;
      case TOKEN_LOCAL:  stmt_locationAddress = LOCAL;   break;
      case TOKEN_SHARED: stmt_locationAddress = SHARED;  break;
      case TOKEN_GLOBAL: stmt_locationAddress = GLOBAL;  break;
      case TOKEN_CONST:  stmt_locationAddress = CONST;   break;
      default:
           assert(0);

    }
  }
  void PTXParser::uninitializableDeclaration( const std::string& name )
  {
  }

  void PTXParser::initializableDeclaration( const std::string& name,  YYLTYPE& one, YYLTYPE& two )
  {
    out 
//      << " extern \"C\"  "
      << locationAddressString(stmt_locationAddress)
      << attributeString(stmt_attribute) 
      << tokenToDataType(tokenDataType)  
      <<  name.c_str() 
      << "[" << nValuesInitializer << "]= { " << decimalList[0];
    int n = decimalList.size();
    for (int i = 1; i < n; i++)
      out << ", " << decimalList[i];
    out << " }; \n";

    assert(decimalList.size() == nValuesInitializer);
    decimalList.clear();
  }


  void PTXParser::assignment()
  {
  }
  void PTXParser::decimalListSingle( long long int value )
  {
    decimalList.push_back(value);
  }
  void PTXParser::decimalListSingle2( long long int value )
  {
    decimalList.push_back(value);
  }

  /****************/

  void PTXParser::arrayDimensionSet( long long int value, YYLTYPE& location, bool add )
  {
    nValuesInitializer = value;
  }
  void PTXParser::arrayDimensionSet()
  {
  }
  void PTXParser::arrayDimensions()
  {
  }

  /****************/

  std::string PTXParser::tokenToDataType( int token )
  {
    switch( token )
    {
      case TOKEN_U8:   return "_u8 "; break;
      case TOKEN_U16:  return "_u16 "; break;
      case TOKEN_U32:  return "_u32 "; break;
      case TOKEN_U64:  return "_u64 "; break;
      case TOKEN_S8:   return "_s8 "; break;
      case TOKEN_S16:  return "_s16 "; break;
      case TOKEN_S32:  return "_s32 "; break;
      case TOKEN_S64:  return "_s64 "; break;
      case TOKEN_B8:   return "_b8 "; break;
      case TOKEN_B16:  return "_b16 "; break;
      case TOKEN_B32:  return "_b32 "; break;
      case TOKEN_B64:  return "_b64 "; break;
      case TOKEN_PRED: return "_pred "; break;
      case TOKEN_F16:  return "_f16 "; break;
      case TOKEN_F32:  return "_f32 "; break;
      case TOKEN_F64:  return "_f64 "; break;
      default: assert(0);
    }

    return "";
  }

  std::string PTXParser::attributeString(attribute_t attr)
  {
    switch (attr)
    {
      case VISIBLE: return " ";
      case EXTERN:  return "_extern "; 
      case WEAK:    return "_weak ";
      case NONE:    return "_static ";
      default:      assert(0);
    };
  }
  std::string PTXParser::locationAddressString(locationAddress_t addr)
  {
    switch (addr)
    {
      case PARAM:  return "_param ";
      case REG:    return "_reg ";
      case LOCAL:  return "_local ";
      case SHARED: return "_shared ";
      case GLOBAL: return "_global ";
      case CONST:  return "_const ";
      default:
           assert(0);
      return  " ";
    }
  }

}

#endif

