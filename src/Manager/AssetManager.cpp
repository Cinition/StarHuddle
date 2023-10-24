#include "AssetManager.h"

#include "Asset/JSONAsset.h"
#include "Asset/TGAAsset.h"
#include "Asset/OGGAsset.h"
#include "Util/StringUtil.h"
#include "Util/PackageUtil.h"
#include "Manager/NotificationManager.h"

#include <raylib.h>
#include <json.hpp>

#include <io.h>
#include <direct.h>
#include <functional>
#include <algorithm>

void AssetManager::importFile( const std::string& _path )
{
	auto payload = loadFile( _path );
	if( !payload.data )
	{
		NotificationManager::addNotification( { "Failed to get data from file." } );
		return;
	}

	auto path      = std::filesystem::path( _path );
	auto name      = path.filename().string();
	auto extension = path.extension().string();

	if( extension == std::string( ".shp" ) )
		PackageUtil::importPackage( _path );
	else if( extension == std::string( ".json" ) )
		m_assets.emplace( m_next_id, std::make_shared< JSONAsset >( m_next_id++, name, extension, payload.data, payload.data_size ) );
	else if( extension == std::string( ".tga" ) )
		m_assets.emplace( m_next_id, std::make_shared< TGAAsset >( m_next_id++, name, extension, payload.data, payload.data_size ) );
	else if( extension == std::string( ".ogg" ) )
		m_assets.emplace( m_next_id, std::make_shared< OGGAsset >( m_next_id++, name, extension, payload.data, payload.data_size ) );
	else
		NotificationManager::addNotification( { "You are trying to insert a file that is not supported!" } );
}

void AssetManager::importAsset( const PackageUtil::PackageData& _package_data, const Asset::Type& _type )
{
	switch( _type )
	{
		case Asset::Type::JSON: m_assets.emplace( m_next_id, std::make_shared< JSONAsset >( m_next_id++, _package_data.name, ".json", static_cast< uint8_t* >( _package_data.data ), _package_data.size ) ); break;
		case Asset::Type::TGA:  m_assets.emplace( m_next_id, std::make_shared< TGAAsset >( m_next_id++, _package_data.name, ".tga", static_cast< uint8_t* >( _package_data.data ), _package_data.size ) ); break;
		case Asset::Type::OGG:  m_assets.emplace( m_next_id, std::make_shared< OGGAsset >( m_next_id++, _package_data.name, ".ogg", static_cast< uint8_t* >( _package_data.data ), _package_data.size ) ); break;
		default: NotificationManager::addNotification( { "You are trying to insert a file that is not supported!" } ); break;
	}
}

void AssetManager::exportAsset( uint32_t _id, const std::string& _path )
{
	auto asset = getAsset( _id );
	if( !asset )
	{
		NotificationManager::addNotification( { "You are trying to export an asset that is unavailable." } );
		return;
	}

	std::string file_path = _path + "\\" + asset->getName();
	if( asset->getType() == Asset::Type::JSON )
		file_path += ".json";
	else if( asset->getType() == Asset::Type::TGA )
		file_path += ".tga";
	else if( asset->getType() == Asset::Type::OGG )
		file_path += ".ogg";

	saveFile( file_path, asset->getData(), asset->getDataSize() );
}

std::shared_ptr< Asset > AssetManager::getAsset( uint32_t _id )
{
	auto asset_it = m_assets.find( _id );
	if( asset_it != m_assets.end() )
		return asset_it->second;

	return nullptr;
}

void AssetManager::addSelection( uint32_t _id )
{
	if( !IsKeyDown( KEY_LEFT_CONTROL ) )
		m_selected_assets.clear();

	m_selected_assets.push_back( _id );
}

void AssetManager::removeSelection( uint32_t _id )
{
	auto selection_it = std::find_if( m_selected_assets.begin(), m_selected_assets.end(), [ _id ]( size_t hash_value ){ return hash_value == _id; } );
	if( selection_it != m_selected_assets.end() )
	{
		m_selected_assets.erase( selection_it );
		return;
	}
}

bool AssetManager::hasAssetsUpdated( void )
{
	size_t checksum{};
	for( auto asset : m_assets )
		checksum ^= std::hash< std::shared_ptr< Asset > >{}( asset.second );

	if( checksum != m_checksum_hash )
	{
		m_checksum_hash = checksum;
		return true;
	}
	return false;
}

AssetManager::file_payload AssetManager::loadFile( const std::string& _path )
{
	auto file_handle = _open( _path.c_str(), 0x0000 | 0x8000, 0777 );
	if( file_handle < 1 )
		return {};

	auto data_size = _lseek( file_handle, 0, 2 );
	if( data_size == 0 )
		return {};

	_lseek( file_handle, 0, 0 );
	uint8_t* data = new uint8_t[ data_size ];
	if( !data )
		return {};

	_read( file_handle, data, data_size );
	_close( file_handle );

	return { data, static_cast< uint32_t >( data_size ) };
}

void AssetManager::saveFile( const std::string& _path, const void* _data, size_t _data_size )
{
	const int32_t file_handle = _open( _path.c_str(), 0x0001 | 0x0100 | 0x0200 | 0x8000, 0777 );
	if( file_handle < 1 )
		return;

	//uint8_t*   data         = static_cast< uint8_t* >( _data );
	const auto written_data = _write( file_handle, _data, static_cast< unsigned int >( _data_size ) );
	if( written_data == 0 )
		return;

	_close( file_handle );
}
