#include "AssetManager.h"

#include "JSONAsset.h"
#include "TGAAsset.h"
#include "OGGAsset.h"

#include "raylib.h"

#include <io.h>
#include <direct.h>
#include <ctime>
#include <functional>
#include <algorithm>

void AssetManager::importFile( const std::string& _path )
{
	auto payload = loadFile( _path );
	if( !payload.data )
		return; // TODO: error popup

	std::filesystem::path file_path            = _path;
	auto                  millisec_since_epoch = duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now().time_since_epoch() ).count();
	auto                  file_hash            = std::hash< uint8_t >{}( *payload.data * millisec_since_epoch * m_next_offset++ );
	if( file_path.extension().string() == std::string( ".json" ) )
		m_assets.push_back( std::make_shared< JSONAsset >( file_hash, file_path, payload.data, payload.data_size ) );
	else if( file_path.extension().string() == std::string( ".tga" ) )
		m_assets.push_back( std::make_shared< TGAAsset >( file_hash, file_path, payload.data, payload.data_size ) );
	else if( file_path.extension().string() == std::string( ".ogg" ) )
		m_assets.push_back( std::make_shared< OGGAsset >( file_hash, file_path, payload.data, payload.data_size ) );
	else
		return; // TODO: error popup

}

void AssetManager::exportAsset( size_t _hash, const std::string& _path )
{
	auto asset = getAsset( _hash );
	if( !asset )
		return; // TODO: error popup

	std::string file_path = _path + "\\" + asset->getName();
	if( asset->getType() == Asset::Type::JSON )
		file_path += ".json";
	else if( asset->getType() == Asset::Type::TGA )
		file_path += ".tga";
	else if( asset->getType() == Asset::Type::OGG )
		file_path += ".ogg";

	saveFile( file_path, asset->getData(), asset->getDataSize() );
}

std::shared_ptr< Asset > AssetManager::getAsset( size_t _hash )
{
	auto asset_it = std::find_if( m_assets.begin(), m_assets.end(),
		[ _hash ]( std::shared_ptr< Asset > _asset )
		{
			return ( _asset->getHash() == _hash );
		} );

	if( asset_it != m_assets.end() )
		return *asset_it;

	return nullptr;
}

void AssetManager::addSelection( size_t _hash )
{
	if( !IsKeyDown( KEY_LEFT_CONTROL ) )
		m_selected_assets.clear();

	m_selected_assets.push_back( _hash );
}

void AssetManager::removeSelection( size_t _hash )
{
	auto selection_it = std::find_if( m_selected_assets.begin(), m_selected_assets.end(), [ _hash ]( size_t hash_value ){ return hash_value == _hash; } );
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
		checksum ^= std::hash< std::shared_ptr< Asset > >{}( asset );

	if( checksum != m_checksum_hash )
	{
		m_checksum_hash = checksum;
		return true;
	}
	return false;
}

AssetManager::file_payload AssetManager::loadFile( const std::string& _path )
{
	const int32_t file_handle = open( _path.c_str(), 0x0000, 0777 );
	if( file_handle < 1 )
		return {}; // TODO: error popup

	const uint32_t data_size = lseek( file_handle, 0, 2 );
	if( data_size == 0 )
		return {}; // TODO: error popup

	lseek( file_handle, 0, 0 ); // seek back to beginning
	uint8_t* data = new uint8_t[ data_size ];
	if( !data )
		return {}; // TODO: error popup

	read( file_handle, data, data_size );
	close( file_handle );

	return { data, data_size };
}

void AssetManager::saveFile( const std::string& _path, void* _data, uint32_t _data_size )
{
	const int32_t file_handle = open( _path.c_str(), 0x0001 | 0x0100 | 0x0200 | 0x8000, 0777 );
	if( file_handle < 1 )
		return; // TODO: error popup

	uint8_t*   data         = static_cast< uint8_t* >( _data );
	const auto written_data = write( file_handle, data, _data_size );
	if( written_data == 0 )
		return; // TODO: error popup

	close( file_handle );
}
