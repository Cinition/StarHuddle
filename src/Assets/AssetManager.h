#pragma once

#include "Asset.h"

#include <map>
#include <string>
#include <memory>

class AssetManager
{

public:

	struct file_payload
	{
		uint8_t* data;
		uint32_t data_size;
	};

	static void                     importFile( const std::string& _path );
	static void                     exportAsset( size_t _hash, const std::string& _path );
	static void                     packageAssets( void );
	static auto                     getAsset( size_t _hash ) -> std::shared_ptr< Asset >;
	static void                     addSelection( size_t _hash );
	static void                     removeSelection( size_t _hash );

	static auto getAssetSelection( void ) { return m_selected_assets; }
	static auto getAssets        ( void ) { return m_assets; }
	static bool hasAssetsUpdated ( void );

private:

	static file_payload loadFile( const std::string& _path );
	static void         saveFile( const std::string& _path, void* _data, uint32_t _data_size);

	inline static std::vector< size_t >                   m_selected_assets;
	inline static std::vector< std::shared_ptr< Asset > > m_assets;
	inline static size_t                                  m_checksum_hash;
	inline static int                                     m_next_offset = 1;

};
