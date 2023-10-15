#include "JSONAsset.h"

#include <filesystem>

JSONAsset::JSONAsset( size_t _hash, const std::filesystem::path& _path, uint8_t* _data, uint32_t _data_size )
{
	m_hash      = _hash;
	m_name      = _path.stem().string();
	m_type      = Asset::Type::JSON;
	m_path      = _path;
	m_data      = _data;
	m_data_size = _data_size;

	handleData( _data );
	createMetaData();
}

void JSONAsset::handleData( uint8_t* _data )
{
}

void JSONAsset::createMetaData( void )
{
	m_meta_data.push_back( "File Size: 55KB" );
	m_meta_data.push_back( "Date Added: 15/10/2023" );
}
