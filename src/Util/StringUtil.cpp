#include "StringUtil.h"

#include <stdarg.h>

std::string StringUtil::format( const char* _string, ... )
{
	va_list     va     = { };
	std::string string = { };

	va_start( va, _string );
	string.resize( vsnprintf( nullptr, 0, _string, va ) );
	va_end( va );

	va_start( va, _string );
	vsnprintf( string.data(), string.length() + 1, _string, va );
	va_end( va );

	return string;

} // format

bool StringUtil::contains( const std::string& _string, const std::string& _contains )
{
	return ( _string.find( _contains ) != std::string::npos );
}
