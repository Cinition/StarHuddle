#include "PackageUtil.h"

#include "Util/FileUtil.h"

namespace PackageUtil
{
	void exportPackage( Package _package )
	{
		const auto file_handle = FileUtil::open( "path", FileUtil::flags::WRITE_ONLY | FileUtil::flags::CREATE | FileUtil::flags::BINARY | FileUtil::flags::TRUNCATE, FileUtil::permissions::WRITE );

		FileUtil::write( file_handle, &_package.header, sizeof( PackageHeader ) );

		for( uint32_t i = 0; i < _package.header.json_count; i++ )
			FileUtil::write( file_handle, _package.json[ i ].data, _package.json[ i ].size );

		for( uint32_t i = 0; i < _package.header.tga_count; i++ )
			FileUtil::write( file_handle, _package.tga[ i ].data, _package.tga[ i ].size );

		for( uint32_t i = 0; i < _package.header.ogg_count; i++ )
			FileUtil::write( file_handle, _package.ogg[ i ].data, _package.ogg[ i ].size );

		FileUtil::close( file_handle );
	}

	auto importPackage( const std::string& _path ) -> Package
	{
		const auto file_handle = FileUtil::open( _path.c_str(), FileUtil::flags::READ_ONLY | FileUtil::flags::BINARY, FileUtil::permissions::READ );

		Package package;
		FileUtil::read( file_handle, &package.header.json_count, sizeof( uint32_t ) );
		FileUtil::read( file_handle, &package.header.tga_count, sizeof( uint32_t ) );
		FileUtil::read( file_handle, &package.header.ogg_count, sizeof( uint32_t ) );

		package.json.reserve( package.header.json_count );
		for( uint32_t i = 0; i < package.header.json_count; i++ )
			package.json[ i ].size = FileUtil::read( file_handle, &package.json[ i ].data, sizeof( uint32_t ) );

		package.tga.reserve( package.header.tga_count );
		for( uint32_t i = 0; i < package.header.tga_count; i++ )
			package.tga[ i ].size = FileUtil::read( file_handle, &package.tga[ i ].data, sizeof( uint32_t ) );

		package.ogg.reserve( package.header.ogg_count );
		for( uint32_t i = 0; i < package.header.ogg_count; i++ )
			package.ogg[ i ].size = FileUtil::read( file_handle, &package.ogg[ i ].data, sizeof( uint32_t ) );

		FileUtil::close( file_handle );
		return package;
	}
}
