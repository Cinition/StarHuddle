#include "JSONFile.h"

JSONFile::JSONFile( const std::filesystem::path& _path, uint8_t* _data )
{
	handleData( _data );
	createMetaData();
}

void JSONFile::handleData( uint8_t* _data )
{
}

void JSONFile::createMetaData( void )
{
}
