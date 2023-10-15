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

	static std::shared_ptr< Asset > getAsset( size_t _hash );
	static void addSelection   ( size_t _hash );
	static void removeSelection( size_t _hash );
	static auto getAssetSelection( void ) { return m_selected_assets; }
	static auto getAssets        ( void ) { return m_assets; }
	static bool hasAssetsUpdated ( void );

private:

	uint8_t* loadFile( const std::string& _path );

	inline static std::vector< size_t >                   m_selected_assets;
	inline static std::vector< std::shared_ptr< Asset > > m_assets;
	inline static size_t                                  m_checksum_hash;
	inline static int                                     m_next_offset = 1;

};
