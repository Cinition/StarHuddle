#pragma once

#include "Files/File.h"

class JSONFile : public File
{

public:

	JSONFile( const std::filesystem::path& _path, uint8_t* _data );

protected:

	void handleData    ( uint8_t* _data );
	void createMetaData( void );

};
