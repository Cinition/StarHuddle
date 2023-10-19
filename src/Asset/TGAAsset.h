#pragma once

#include "Asset/Asset.h"

class TGAAsset : public Asset
{

public:

	TGAAsset( size_t _hash, const std::filesystem::path& _path, uint8_t* _data, uint32_t _data_size );

protected:

	void handleData    ( uint8_t* _data );
	void createMetaData( void );

private:

#pragma pack( push, 1 )
	struct TGAHeader
	{
		uint8_t  id_length;
		uint8_t  colour_map_type;
		uint8_t  data_type_code;
		uint16_t colour_map_origin;
		uint16_t colour_map_length;
		uint8_t  colour_map_depth;
		uint16_t x_origin;
		uint16_t y_origin;
		uint16_t width;
		uint16_t height;
		uint8_t  bits_per_pixel;
		uint8_t  image_descriptor;
	};
#pragma pack( pop )

	TGAHeader m_header;

};
