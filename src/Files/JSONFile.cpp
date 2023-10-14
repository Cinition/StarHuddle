#include "JSONFile.h"

#include <filesystem>

JSONFile::JSONFile( size_t _hash, const std::filesystem::path& _path, uint8_t* _data )
{
	m_hash = _hash;
	m_name = _path.stem().string();
	m_type = File::Type::JSON;
	m_path = _path;

	handleData( _data );
	createMetaData();
}

void JSONFile::handleData( uint8_t* _data )
{
}

void JSONFile::createMetaData( void )
{
}
