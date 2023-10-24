#pragma once

#include "Asset/Asset.h"
#include "Util/PackageUtil.h"

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

	static void importFile( const std::string& _path );
	static void importAsset( const PackageUtil::PackageData& _package_data, const Asset::Type& _type );
	static void exportAsset( uint32_t _hash, const std::string& _path );
	static auto getAsset( uint32_t _hash ) -> std::shared_ptr< Asset >;
	static void addSelection( uint32_t _hash );
	static void removeSelection( uint32_t _hash );

	static auto getAssetSelection( void ) { return m_selected_assets; }
	static auto getAssets        ( void ) { return m_assets; }
	static bool hasAssetsUpdated ( void );

private:

	static file_payload loadFile( const std::string& _path );
	static void         saveFile( const std::string& _path, const void* _data, size_t _data_size);

	inline static std::vector< uint32_t >                        m_selected_assets;
	inline static std::map< uint32_t, std::shared_ptr< Asset > > m_assets;
	inline static size_t                                         m_checksum_hash;
	inline static int                                            m_next_id = 1;

};
