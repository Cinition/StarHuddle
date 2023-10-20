#include "FilterManager.h"

#include "Util/StringUtil.h"

bool FilterManager::getsFilteredOut( const Asset& _asset )
{
	if( StringUtil::contains( _asset.getName(), m_name_filter ) )
		return false;

	return true;
}
