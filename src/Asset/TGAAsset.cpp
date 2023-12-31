#include "TGAAsset.h"

#include "Util/StringUtil.h"

#include <filesystem>

TGAAsset::TGAAsset( uint32_t _id, const std::string& _name, const std::string& _extension, uint8_t* _data, uint32_t _data_size )
{
	m_id        = _id;
	m_name      = _name;
	m_extension = _extension;
	m_type      = Asset::Type::TGA;
	m_texture   = LoadTexture( "../data/textures/TGA.png" );
	m_data      = _data;
	m_data_size = _data_size;

	handleData( _data );
	createMetaData();
}

void TGAAsset::handleData( uint8_t* _data )
{
	TGAHeader header = *reinterpret_cast< TGAHeader* >( _data );
	m_header         = header;
}

void TGAAsset::createMetaData( void )
{
	auto time = std::time( nullptr );
	char time_string[ std::size( "dd/mm/yyyy hh::mm" ) ];
	std::strftime( std::data( time_string ), std::size( time_string ), "%d/%m/%Y %H:%M", std::localtime( &time ) );

	m_meta_data.push_back( { "Size:", StringUtil::format( "%iKB", ( m_data_size / 1024 ) ) } );
	m_meta_data.push_back( { "Added:", time_string } );
	m_meta_data.push_back( { "Resolution:", StringUtil::format( "%ix%i", m_header.width, m_header.height ) } );
	m_meta_data.push_back( { "Bits Per Pixel:", StringUtil::format( "%i", m_header.bits_per_pixel ) } );
}
