#pragma once

#include <string>

namespace StringUtil
{
	extern std::string format  ( const char* _string, ... );
	extern bool        contains( const std::string& _string, const std::string& _contains );
}
