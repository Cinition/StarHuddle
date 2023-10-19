#pragma once

#include <stdint.h>
#include <vector>

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
		void*    data;
		uint32_t size;
	};

	struct Package
	{
		PackageHeader header;
		std::vector< PackageData > json;
		std::vector< PackageData > tga;
		std::vector< PackageData > ogg;
	};

	extern void exportPackage( Package _package );
	extern auto importPackage( const std::string& _path ) -> Package;
}
