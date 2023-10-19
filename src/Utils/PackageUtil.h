#pragma once

#include <stdint.h>

namespace PackageUtil
{
	struct PackageHeader
	{
		uint32_t json_count;
		uint32_t tga_count;
		uint32_t ogg_count;
	};

	struct PackageData
	{
		void*    json_data;
		uint32_t json_data_size;
		void*    tga_data;
		uint32_t tga_data_size;
		void*    ogg_data;
		uint32_t ogg_data_size;
	};

	extern void exportPackage( PackageHeader _header, PackageData _data );
}
