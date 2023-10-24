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

		FileUtil::write( file_handle, &_package.header.json_count, sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.tga_count, sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.ogg_count, sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.package_size, sizeof( uint32_t ) );
		FileUtil::write( file_handle, &_package.header.compressed_size, sizeof( uint32_t ) );

		for( uint32_t i = 0; i < _package.header.json_count; i++ )
		{
			auto name_size = _package.json[ i ].name.size();
			char* name      = new char[ name_size ];
			FileUtil::write( file_handle, &name_size, sizeof( size_t ) );
			FileUtil::write( file_handle, name, static_cast< uint32_t >( name_size ) );
			FileUtil::write( file_handle, &_package.json[ i ].size, sizeof( uint32_t ) );
			_package.json[ i ].name = name;
		}

		for( uint32_t i = 0; i < _package.header.tga_count; i++ )
		{
			auto name_size = _package.tga[ i ].name.size();
			char* name      = new char[ name_size ];
			FileUtil::write( file_handle, &name_size, sizeof( size_t ) );
			FileUtil::write( file_handle, name, static_cast< uint32_t >( name_size ) );
			FileUtil::write( file_handle, &_package.tga[ i ].size, sizeof( uint32_t ) );
			_package.tga[ i ].name = name;
		}

		for( uint32_t i = 0; i < _package.header.ogg_count; i++ )
		{
			auto name_size = _package.ogg[ i ].name.size();
			char* name      = new char[ name_size ];
			FileUtil::write( file_handle, &name_size, sizeof( size_t ) );
			FileUtil::write( file_handle, name, static_cast< uint32_t >( name_size ) );
			FileUtil::write( file_handle, &_package.ogg[ i ].size, sizeof( uint32_t ) );
			_package.ogg[ i ].name = name;
		}

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
		FileUtil::read( file_handle, &package.header.package_size, sizeof( uint32_t ) );
		FileUtil::read( file_handle, &package.header.compressed_size, sizeof( uint32_t ) );

		// read data sizes
		for( uint32_t i = 0; i < package.header.json_count; i++ )
		{
			PackageData package_data;
			size_t      name_size;
			FileUtil::read( file_handle, &name_size, sizeof( size_t ) );

			char* name = new char[ name_size ];
			FileUtil::read( file_handle, name, static_cast< uint32_t >( name_size ) );
			package_data.name = name;

			FileUtil::read( file_handle, &package_data.size, sizeof( uint32_t ) );
			package.json.push_back( package_data );
		}

		for( uint32_t i = 0; i < package.header.tga_count; i++ )
		{
			PackageData package_data;
			size_t      name_size;
			FileUtil::read( file_handle, &name_size, sizeof( size_t ) );

			char* name = new char[ name_size ];
			FileUtil::read( file_handle, name, static_cast< uint32_t >( name_size ) );
			package_data.name = name;

			FileUtil::read( file_handle, &package_data.size, sizeof( uint32_t ) );
			package.tga.push_back( package_data );
		}

		for( uint32_t i = 0; i < package.header.ogg_count; i++ )
		{
			PackageData package_data;
			size_t      name_size;
			FileUtil::read( file_handle, &name_size, sizeof( size_t ) );

			char* name = new char[ name_size ];
			FileUtil::read( file_handle, name, static_cast< uint32_t >( name_size ) );
			package_data.name = name;

			FileUtil::read( file_handle, &package_data.size, sizeof( uint32_t ) );
			package.ogg.push_back( package_data );
		}

		void* data = malloc( static_cast< size_t >( package.header.compressed_size ) );
		FileUtil::read( file_handle, &data, package.header.compressed_size );

		auto  decompressed_size = static_cast< size_t >( package.header.package_size );
		void* decompressed_data = malloc( decompressed_size );
		ZSTD_decompress( decompressed_data, decompressed_size, data, static_cast< size_t >( package.header.compressed_size ) );

		// read the actual data
		for( uint32_t i = 0; i < package.header.json_count; i++ )
		{
			PackageData& package_data = package.json[ i ];
			package_data.data         = malloc( static_cast< size_t >( package.json[ i ].size ) );
			FileUtil::read( file_handle, &package_data.data, package.json[ i ].size );
		}

		for( uint32_t i = 0; i < package.header.tga_count; i++ )
		{
			PackageData& package_data = package.tga[ i ];
			package_data.data         = malloc( static_cast< size_t >( package.tga[ i ].size ) );
			FileUtil::read( file_handle, &package_data.data, package.tga[ i ].size );
		}

		for( uint32_t i = 0; i < package.header.ogg_count; i++ )
		{
			PackageData& package_data = package.ogg[ i ];
			package_data.data         = malloc( static_cast< size_t >( package.ogg[ i ].size ) );
			FileUtil::read( file_handle, &package_data.data, package.ogg[ i ].size );
		}

		// Done loading packaged assets
		// So we import into the AssetManager
		for( auto& package_data : package.json )
			AssetManager::importAsset( package_data, Asset::Type::JSON );

		for( auto& package_data : package.tga )
			AssetManager::importAsset( package_data, Asset::Type::TGA );

		for( auto& package_data : package.ogg )
			AssetManager::importAsset( package_data, Asset::Type::OGG );

	}
}
