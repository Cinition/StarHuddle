#include "PackageUtil.h"

#include "Util/FileUtil.h"
#include "Util/StringUtil.h"
#include "Manager/NotificationManager.h"

#include <zstd.h>
#include <filesystem>

namespace PackageUtil
{
	void exportPackage( const Package& _package, const std::string& _path )
	{
		const auto file_handle = FileUtil::open( _path, FileUtil::flags::WRITE_ONLY | FileUtil::flags::CREATE | FileUtil::flags::BINARY | FileUtil::flags::TRUNCATE, FileUtil::permissions::WRITE );
		if( file_handle < 1 )
			return;

		FileUtil::write( file_handle, &_package.header.json_count,   sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.tga_count,    sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.ogg_count,    sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.package_size, sizeof( uint32_t ) );

		for( uint32_t i = 0; i < _package.header.json_count; i++ )
			FileUtil::write( file_handle, _package.json[ i ].data, _package.json[ i ].size );

		for( uint32_t i = 0; i < _package.header.tga_count; i++ )
			FileUtil::write( file_handle, _package.tga[ i ].data, _package.tga[ i ].size );

		for( uint32_t i = 0; i < _package.header.ogg_count; i++ )
			FileUtil::write( file_handle, _package.ogg[ i ].data, _package.ogg[ i ].size );

		FileUtil::close( file_handle );
	}
}
