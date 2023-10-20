#pragma once

#include "Asset/Asset.h"

#include <string>

class FilterManager
{
public:

	static bool getsFilteredOut( const Asset& _asset );
	static void setNameFilter( const std::string& _input ) { m_name_filter = _input; }

private:

	inline static std::string m_name_filter;

};
