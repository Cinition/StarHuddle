#include "PackageUtil.h"

#include "Util/FileUtil.h"
#include "Util/StringUtil.h"
#include "Manager/NotificationManager.h"
#include "Manager/AssetManager.h"

#include <zstd.h>
#include <filesystem>

namespace PackageUtil
{
	void exportPackage( Package& _package, const std::string& _path )
	{
		uint8_t* data = new uint8_t[ _package.header.package_size ];

		auto data_copying = [ data ]( std::vector< PackageData >& _copy_src )
		{
			for( auto& package_data : _copy_src )
				memcpy( data, package_data.data, static_cast< size_t >( package_data.size ) );
		};

		data_copying( _package.json );
		data_copying( _package.tga );
		data_copying( _package.ogg );
		// MARKER: Data Copying

		auto  bound_size      = ZSTD_compressBound( _package.header.package_size );
		void* compressed_data = malloc( static_cast< size_t >( bound_size ) );
		auto  compressed_size = ZSTD_compress( compressed_data, bound_size, data, static_cast< size_t >( _package.header.package_size ), 1 );
		
		_package.header.compressed_size = static_cast< uint32_t >( compressed_size );

		const auto file_handle = FileUtil::open( _path, FileUtil::flags::WRITE_ONLY | FileUtil::flags::CREATE | FileUtil::flags::BINARY | FileUtil::flags::TRUNCATE, FileUtil::permissions::WRITE );
		if( file_handle < 1 )
			return;

		FileUtil::write( file_handle, &_package.header.json_count, sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.tga_count, sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.ogg_count, sizeof( uint32_t ) );
		// MARKER: Writing Format Count

		FileUtil::write( file_handle, &_package.header.package_size, sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.compressed_size, sizeof( uint32_t ) );

		auto data_writing = [ file_handle ]( std::vector< PackageData >& _header_data )
		{
			for( auto& package_data : _header_data )
			{
				auto  name_size = package_data.name.size();
				char* name      = new char[ name_size ];
				FileUtil::write( file_handle, &name_size, sizeof( size_t ) );
				FileUtil::write( file_handle, name, static_cast< uint32_t >( name_size ) );
				FileUtil::write( file_handle, &package_data.size, sizeof( uint32_t ) );
				package_data.name = name;
			}
		};

		data_writing( _package.json );
		data_writing( _package.tga );
		data_writing( _package.ogg );
		// MARKER: Writing Data Struct

		FileUtil::write( file_handle, compressed_data, static_cast< uint32_t >( compressed_size ) );

		FileUtil::close( file_handle );
	}

	void importPackage( const std::string& _path )
	{
		const auto file_handle = FileUtil::open( _path, FileUtil::flags::READ_ONLY | FileUtil::flags::BINARY, FileUtil::permissions::READ );
		if( file_handle < 1 )
			return;

		Package package;

		FileUtil::read( file_handle, &package.header.json_count, sizeof( uint32_t ) );
		FileUtil::read( file_handle, &package.header.tga_count, sizeof( uint32_t ) );
		FileUtil::read( file_handle, &package.header.ogg_count, sizeof( uint32_t ) );
		// MARKER: Reading Format Count

		FileUtil::read( file_handle, &package.header.package_size, sizeof( uint32_t ) );
		FileUtil::read( file_handle, &package.header.compressed_size, sizeof( uint32_t ) );

		auto data_header_reading = [ file_handle ]( uint32_t _count )
		{
			std::vector< PackageData > packages;

			for( uint32_t i = 0; i < _count; i++ )
			{
				PackageData package_data;
				size_t      name_size;
				FileUtil::read( file_handle, &name_size, sizeof( size_t ) );

				char* name = new char[ name_size ];
				FileUtil::read( file_handle, name, static_cast< uint32_t >( name_size ) );
				package_data.name = name;

				FileUtil::read( file_handle, &package_data.size, sizeof( uint32_t ) );
				packages.push_back( package_data );
			}

			return packages;
		};

		// read data sizes
		package.json = std::move( data_header_reading( package.header.json_count ) );
		package.tga = std::move( data_header_reading( package.header.tga_count ) );
		package.ogg = std::move( data_header_reading( package.header.ogg_count ) );
		// MARKER: Reading Data Headers

		void* data = malloc( static_cast< size_t >( package.header.compressed_size ) );
		FileUtil::read( file_handle, &data, package.header.compressed_size );

		auto  decompressed_size = static_cast< size_t >( package.header.package_size );
		void* decompressed_data = malloc( decompressed_size );
		ZSTD_decompress( decompressed_data, decompressed_size, data, static_cast< size_t >( package.header.compressed_size ) );

		auto data_reading = [ file_handle ]( std::vector< PackageData >& _type_data )
		{
			for( auto& package_data : _type_data )
			{
				package_data.data = malloc( static_cast< size_t >( package_data.size ) );
				FileUtil::read( file_handle, &package_data.data, package_data.size );
			}
		};

		// read the actual data
		data_reading( package.json );
		data_reading( package.tga );
		data_reading( package.ogg );
		// MARKER: Reading Data

		// import assets into the asset manager
		auto import_asset = []( std::vector< PackageData > _data, const Asset::Type& _type )
		{
			for( auto& package_data : _data )
				AssetManager::importAsset( package_data, _type );
		};

		import_asset( package.json, Asset::Type::JSON );
		import_asset( package.tga, Asset::Type::TGA );
		import_asset( package.ogg, Asset::Type::OGG );
		// MARKER: Importing Asset

	}
}
