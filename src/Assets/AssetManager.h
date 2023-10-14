#pragma once

#include "Asset.h"

#include <map>
#include <string>
#include <memory>

class AssetManager
{

public:

	void importFile     ( const std::string& _path );
	void exportFile     ( void );
	void addSelection   ( size_t _hash, bool _clear_selection = true );
	void removeSelection( size_t _hash );

	auto getAssetSelection( void ) const { return m_selected_files; }
	auto getAssets        ( void ) const { return m_files; }

private:

	uint8_t* loadFile( const std::string& _path );

	inline static std::vector< size_t >                        m_selected_files;
	inline static std::map< size_t, std::shared_ptr< Asset > > m_files;

};
