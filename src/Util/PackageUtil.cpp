#include "PackageUtil.h"

#include "Util/FileUtil.h"
#include "Util/StringUtil.h"
#include "Manager/NotificationManager.h"

#include <zstd.h>
#include <filesystem>

namespace PackageUtil
{
	void exportPackage( Package& _package, const std::string& _path )
	{
		uint8_t* data = new uint8_t[ _package.header.package_size ];
		for( uint32_t i = 0; i < _package.header.json_count; i++ )
			memcpy( data, _package.json[ i ].data, static_cast< size_t >( _package.json[ i ].size ) );

		for( uint32_t i = 0; i < _package.header.tga_count; i++ )
			memcpy( data, _package.tga[ i ].data, static_cast< size_t >( _package.tga[ i ].size ) );

		for( uint32_t i = 0; i < _package.header.ogg_count; i++ )
			memcpy( data, _package.ogg[ i ].data, static_cast< size_t >( _package.ogg[ i ].size ) );

		auto  bound_size      = ZSTD_compressBound( _package.header.package_size );
		void* compressed_data = malloc( static_cast< size_t >( bound_size ) );
		auto  compressed_size = ZSTD_compress( compressed_data, bound_size, data, static_cast< size_t >( _package.header.package_size ), 1 );
		
		_package.header.compressed_size = static_cast< uint32_t >( compressed_size );

		const auto file_handle = FileUtil::open( _path, FileUtil::flags::WRITE_ONLY | FileUtil::flags::CREATE | FileUtil::flags::BINARY | FileUtil::flags::TRUNCATE, FileUtil::permissions::WRITE );
		if( file_handle < 1 )
			return;

		FileUtil::write( file_handle, &_package.header.json_count,   sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.tga_count,    sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.ogg_count,    sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.package_size, sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.compressed_size, sizeof( uint32_t ) );

		FileUtil::write( file_handle, compressed_data, static_cast< uint32_t >( compressed_size ) );

		FileUtil::close( file_handle );
	}
}
