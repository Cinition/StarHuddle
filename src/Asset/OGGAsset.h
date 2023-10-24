#pragma once

#include "Asset/Asset.h"

class OGGAsset : public Asset
{

public:

	OGGAsset( uint32_t _id, const std::string& _name, const std::string& _extension, uint8_t* _data, uint32_t _data_size );

protected:

	void handleData    ( uint8_t* _data );
	void createMetaData( void );

};
