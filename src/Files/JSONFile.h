#pragma once

#include "Files/File.h"

class JSONFile : public File
{

public:

	using File::File;

private:

	void handleData    ( uint8_t* _data );
	void createMetaData( void );

};
