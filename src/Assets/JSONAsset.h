#pragma once

#include "Assets/Asset.h"

class JSONAsset : public Asset
{

public:

	JSONAsset( size_t _hash, const std::filesystem::path& _path, uint8_t* _data, uint32_t _data_size );

protected:

	void handleData( uint8_t* /*_data*/ ){};
	void createMetaData( void );

};
