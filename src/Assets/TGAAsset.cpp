#include "TGAAsset.h"

#include <filesystem>

TGAAsset::TGAAsset( size_t _hash, const std::filesystem::path& _path, uint8_t* _data, uint32_t _data_size )
{
	m_hash      = _hash;
	m_name      = _path.stem().string();
	m_type      = Asset::Type::TGA;
	m_path      = _path;
	m_data      = _data;
	m_data_size = _data_size;

	handleData( _data );
	createMetaData();
}

void TGAAsset::handleData( uint8_t* _data )
{
}

void TGAAsset::createMetaData( void )
{
	m_meta_data.push_back( "File Size: 125KB" );
	m_meta_data.push_back( "Date Added: 12/10/2023" );

}
