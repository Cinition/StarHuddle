#include "PackageUtil.h"

#include "Util/FileUtil.h"
#include "Util/StringUtil.h"
#include "Manager/NotificationManager.h"

#include <zstd.h>
#include <filesystem>

namespace PackageUtil
{
	void exportPackage( Package _package, const std::string& _path )
	{
		auto        package_data    = serializePackage( _package );
		auto        comp_size       = ZSTD_compressBound( _package.header.package_size );
		void*       comp_package    = malloc( static_cast< size_t >( comp_size ) );

		auto        compress_result = ZSTD_compress( &comp_package, comp_size, &package_data, static_cast< size_t >( _package.header.package_size ), 1 );
		if( ZSTD_isError( compress_result ) )
		{
			NotificationManager::addNotification( { "Something went wrong with compression" } );
			return;
		}

		const auto file_handle = FileUtil::open( _path.c_str(), FileUtil::flags::WRITE_ONLY | FileUtil::flags::CREATE | FileUtil::flags::BINARY | FileUtil::flags::TRUNCATE, FileUtil::permissions::WRITE );
		FileUtil::write( file_handle, &comp_package, static_cast< uint32_t >( compress_result ) );
		FileUtil::close( file_handle );
	}

	auto serializePackage( Package _package ) -> uint8_t*
	{
		const auto file_handle = FileUtil::open( WORKING_DIRECTORY, FileUtil::flags::WRITE_ONLY | FileUtil::flags::CREATE | FileUtil::flags::BINARY | FileUtil::flags::TRUNCATE, FileUtil::permissions::WRITE );

		FileUtil::write( file_handle, &_package.header.json_count, sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.tga_count, sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.ogg_count, sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.package_size, sizeof( uint32_t ) );

		for( uint32_t i = 0; i < _package.header.json_count; i++ )
			FileUtil::write( file_handle, _package.json[ i ].data, _package.json[ i ].size );

		for( uint32_t i = 0; i < _package.header.tga_count; i++ )
			FileUtil::write( file_handle, _package.tga[ i ].data, _package.tga[ i ].size );

		for( uint32_t i = 0; i < _package.header.ogg_count; i++ )
			FileUtil::write( file_handle, _package.ogg[ i ].data, _package.ogg[ i ].size );

		uint8_t* package_buffer = static_cast< uint8_t* >( malloc( static_cast< size_t >( _package.header.package_size ) ) );
		FileUtil::seek( file_handle, 0, 0 ); // reset file cursor
		FileUtil::read( file_handle, &package_buffer, _package.header.package_size );

		return package_buffer;
	}
}
