#include "JSONAsset.h"

#include <filesystem>

JSONAsset::JSONAsset( size_t _hash, const std::filesystem::path& _path, uint8_t* _data )
{
	m_hash = _hash;
	m_name = _path.stem().string();
	m_type = Asset::Type::JSON;
	m_path = _path;

	handleData( _data );
	createMetaData();
}

void JSONAsset::handleData( uint8_t* _data )
{
}

void JSONAsset::createMetaData( void )
{
}
