#include "StringHelper.h"

#include <stdarg.h>

std::string StringHelper::format( const char* _string, ... )
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
