/*! \file PTXParser.h
	\date Monday January 19, 2009
	\author Gregory Diamos <gregory.diamos@gatech.edu>
	\brief The header file for the PTXParser class.
*/

#ifndef PTX_PARSER_H_INCLUDED
#define PTX_PARSER_H_INCLUDED


#undef yyFlexLexer
#define yyFlexLexer ptxFlexLexer
#include <FlexLexer.h>


#include "PTXLexer.h"

#include <vector>

namespace parser
{
  /*! \brief An implementation of the Parser interface for PTX */
  class PTXParser 
  {
    public:
      unsigned int alignment;

    public:
      void addSpecialRegisters();

      void maxnreg( unsigned int regs );
      void maxntid( unsigned int tidx, unsigned int tidy = 1024, 
          unsigned int tidz = 1024 );
      void ctapersm( int target, unsigned int ctas );
      void maxnctapersm( unsigned int ctas );
      void maxnctapersm();
      void minnctapersm( unsigned int ctas );
      void minnctapersm();

    public:
      void preprocessor( int token );
      void version( double version, YYLTYPE& location );
      void addressSize( unsigned int size );
      void identifierList( const std::string& identifier );
      void identifierList2( const std::string& identifier );
      void decimalListSingle( long long int value );
      void decimalListSingle2( long long int value );
      void symbolListSingle( const std::string& identifier );
      void symbolListSingle2( const std::string& identifier );
      void floatList( double value );
      void floatList1( double value );
      void singleList( float value );
      void singleList1( float value );
      void targetElement( int token );
      void target();
      void noAddressSpace();
      void addressSpace( int token );
      void dataType( int token );
      void statementVectorType( int token );
      void instructionVectorType( int token );
      void attribute( bool visible, bool external, bool weak );
      void shiftAmount( bool shift );
      void vectorIndex( int token );

      void arrayDimensionSet( long long int value, 
          YYLTYPE& location, bool add );
      void arrayDimensionSet();
      void arrayDimensions();
      void assignment();
      void registerDeclaration( const std::string& name, 
          YYLTYPE& location, unsigned int regs = 0 );
      void registerSeperator( YYLTYPE& location );
      void fileDeclaration( unsigned int id, 
          const std::string& name );
      void initializableDeclaration( const std::string& name, 
          YYLTYPE& one, YYLTYPE& two );
      void textureDeclaration( int token,const std::string& name, 
          YYLTYPE& location );
      void surfaceDeclaration( int token, 
          const std::string &name, YYLTYPE &location);
      void samplerDeclaration( int token, 
          const std::string &name, YYLTYPE &location);
      void argumentDeclaration( const std::string& name, 
          YYLTYPE& location );
      void paramArgumentDeclaration(int token);

      void openBrace( YYLTYPE& location );
      void closeBrace( YYLTYPE& location );
      void returnArgumentListBegin( YYLTYPE& location );
      void returnArgumentListEnd( YYLTYPE& location );
      void argumentListBegin( YYLTYPE& location );
      void argumentListEnd( YYLTYPE& location );

      void functionBegin( YYLTYPE& location );
      void functionName( const std::string& name, 
          YYLTYPE& location );
      void functionDeclaration( YYLTYPE& location, bool body );

      void entry( const std::string& name, YYLTYPE& location );
      void entryDeclaration( YYLTYPE& location );
      void entryPrototype( YYLTYPE& location );
      void entryStatement( YYLTYPE& location );
      void metadata( const std::string& comment );

      void locationAddress( int token );
      void uninitializableDeclaration( const std::string& name );
      void location( long long int one, long long int two, 
          long long int three );
      void label( const std::string& string );
      void pragma( const std::string& string );
      void labelOperand( const std::string& string );
      void nonLabelOperand( const std::string& string, 
          YYLTYPE& location, bool invert );
      void constantOperand( long long int value );
      void constantOperand( unsigned long long int value );
      void constantOperand( float value );
      void constantOperand( double value );
      void indexedOperand( const std::string& name, 
          YYLTYPE& location, long long int value );
      void addressableOperand( const std::string& name, 
          long long int value, YYLTYPE& location, 
          bool invert );
      void arrayOperand( YYLTYPE& location );
      void returnOperand();
      void guard( const std::string& name, YYLTYPE& one, 
          bool invert );
      void guard();
      void statementEnd( YYLTYPE& location );

      void tail( bool condition );
      void uni( bool condition );
      void carry( bool condition );
      void modifier( int token );
      void atomic( int token );
      void volatileFlag( bool condition );
      void reduction( int token );
      void comparison( int token );
      void boolean( int token );
      void geometry( int token );
      void vote( int token );
      void shuffle( int token );
      void level( int token );
      void permute( int token );
      void floatingPointMode( int token );
      void defaultPermute();
      void full();

      void instruction();
      void instruction( const std::string& opcode, int dataType );
      void instruction( const std::string& opcode );
      void tex( int dataType );
      void tld4( int dataType );
      void callPrototypeName( const std::string& identifier );
      void call( const std::string& identifier,
          YYLTYPE& location );
      void carryIn();
      void relaxedConvert( int token, YYLTYPE& location );
      void cvtaTo();
      void convert( int token, YYLTYPE& location );
      void convertC( int token, YYLTYPE& location );
      void convertD( int token, YYLTYPE& location )  { }
      void operandCIsAPredicate();
      void barrierOperation( int token, YYLTYPE & location);
      void cacheOperation(int token );
      void cacheLevel(int token );
      void clampOperation(int token);
      void formatMode(int token);
      void surfaceQuery(int token);
      void colorComponent(int token);

      void returnType( int token );
      void argumentType( int token );
      void callPrototype( const std::string& name, 
          const std::string& identifier, YYLTYPE& location );
      void callTargets( const std::string& name, 
          YYLTYPE& location );
  };

}

#endif

