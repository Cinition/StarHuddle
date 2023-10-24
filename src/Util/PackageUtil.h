#pragma once

#include <stdint.h>
#include <string>
#include <vector>

namespace PackageUtil
{
	struct PackageHeader
	{
		uint32_t json_count;
		uint32_t tga_count;
		uint32_t ogg_count;
		uint32_t package_size;
		uint32_t compressed_size;
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

	extern void exportPackage( Package& _package, const std::string& _path );
	extern auto serializePackage( const Package& _package ) -> uint8_t*;
}
