#include "AssetManager.h"

#include "JSONAsset.h"

#include "raylib.h"

#include <io.h>
#include <direct.h>
#include <ctime>
#include <functional>
#include <iostream>
#include <algorithm>

void AssetManager::importFile( const std::string& _path )
{
	auto data = loadFile( _path );
	if( !data )
		return; // TODO: error popup

	std::filesystem::path file_path            = _path;
	auto                  millisec_since_epoch = duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now().time_since_epoch() ).count();
	auto                  file_hash            = std::hash< uint8_t >{}( *data * millisec_since_epoch * m_next_offset++ );
	if( file_path.extension().string() == std::string( ".json" ) )
		m_assets.push_back( std::make_shared< JSONAsset >( file_hash, file_path, data ) );
	else
		return; // TODO: error popup

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

uint8_t* AssetManager::loadFile( const std::string& _path )
{
	const int32_t file_handle = open( _path.c_str(), 0X0000, 0444 );
	if( file_handle < 1 )
		return nullptr; // TODO: error popup

	const uint32_t data_size = lseek( file_handle, 0, 2 );
	if( data_size == 0 )
		return nullptr; // TODO: error popup

	lseek( file_handle, 0, 0 ); // seek back to beginning
	uint8_t* data = new uint8_t[ data_size ];
	if( !data )
		return nullptr; // TODO: error popup

	read( file_handle, data, data_size );
	close( file_handle );

	return data;
}
