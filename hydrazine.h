#pragma once

static	long long unsigned int hydrazine_binaryToUint( const std::string& string )
{
  long long unsigned int result = 0;
  assert( string.size() > 2 );

  std::string::const_iterator ci = string.begin();
  assert( *ci == '0' );
  ++ci;
  assert( *ci == 'b' );
  ++ci;

  long long unsigned int mask = 1;

  for( ; ci != string.end(); ++ci )
  {
    assert( *ci == '0' || *ci == '1' );

    result |= mask & ( *ci == '1' );
    mask <<= 1;
  }

  return result;
}

static void hydrazine_strlcpy( char* dest, const char* src, unsigned int length )
{
  const char* end = src + ( length - 1 );
  for( ; src != end; ++src, ++dest )
  {
    *dest = *src;	
    if( *src == '\0' )
    {
      return;
    }
  }
  *dest = '\0';
}
