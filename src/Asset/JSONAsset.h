#pragma once

#include "Asset/Asset.h"

class JSONAsset : public Asset
{

public:

	JSONAsset( uint32_t _id, const std::string& _name, const std::string& _extension, uint8_t* _data, uint32_t _data_size );

protected:

	void handleData( uint8_t* /*_data*/ ){};
	void createMetaData( void );

};
