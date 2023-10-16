#include "OGGAsset.h"

#include "Utils/StringHelper.h"

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

void OGGAsset::handleData( uint8_t* /*_data*/ )
{
	// Implement Vorbig OGG headerpage reading
}

void OGGAsset::createMetaData( void )
{
	auto time = std::time( nullptr );
	char time_string[ std::size( "dd/mm/yyyy hh::mm" ) ];
	std::strftime( std::data( time_string ), std::size( time_string ), "%d/%m/%Y %H:%M", std::localtime( &time ) );

	m_meta_data.push_back( { "Size:", StringHelper::format( "%iKB", ( m_data_size / 1024 ) ) } );
	m_meta_data.push_back( { "Added:", time_string } );
}
