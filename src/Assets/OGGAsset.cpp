#include "OGGAsset.h"

#include <filesystem>

OGGAsset::OGGAsset( size_t _hash, const std::filesystem::path& _path, uint8_t* _data, uint32_t _data_size )
{
	m_hash      = _hash;
	m_name      = _path.stem().string();
	m_type      = Asset::Type::OGG;
	m_path      = _path;
	m_data      = _data;
	m_data_size = _data_size;

	handleData( _data );
	createMetaData();
}

void OGGAsset::handleData( uint8_t* _data )
{
}

void OGGAsset::createMetaData( void )
{
	m_meta_data.push_back( "File Size: 235KB" );
	m_meta_data.push_back( "Date Added: 7/10/2023" );

}
