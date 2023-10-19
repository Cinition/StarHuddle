#include "TopBar.h"

#include "Manager/AssetManager.h"
#include "Manager/NotificationManager.h"
#include "UI/Layout.h"
#include "UI/Style.h"
#include "Util/FileUtil.h"
#include "Util/StringUtil.h"

TopBar::TopBar( void )
: UIElement( Vector2( 0.f, 0.f ), Vector2( 0.f, 0.f ) )
, m_package_button( "Package", LAYOUT::TOPBAR::PACKAGE_POS, LAYOUT::TOPBAR::PACKAGE_SIZE, TopBar::packageAssets )
, m_import_button( LoadTexture( "../data/textures/ImportIcon.png" ), Vector2( 22.5f, 22.5f ), LAYOUT::TOPBAR::IMPORT_POS, LAYOUT::TOPBAR::IMPORT_SIZE, TopBar::importFile )
, m_export_button( LoadTexture( "../data/textures/ExportIcon.png" ), Vector2( 22.5f, 22.5f ), LAYOUT::TOPBAR::EXPORT_POS, LAYOUT::TOPBAR::EXPORT_SIZE, TopBar::exportFile )
, m_search_input( LAYOUT::TOPBAR::SEARCH_POS, LAYOUT::TOPBAR::SEARCH_SIZE )
{
}

void TopBar::update( const float _tick )
{
	m_package_button.update( _tick );
	m_import_button.update( _tick );
	m_export_button.update( _tick );
	m_search_input.update( _tick );
}

void TopBar::draw( void )
{
	m_import_button.draw();
	m_export_button.draw();
	m_search_input.draw();
	m_package_button.draw();
}

void TopBar::packageAssets( void )
{
}

void TopBar::importFile( void )
{
	AssetManager asset_manager;
	auto paths = FileUtil::openFileDialog();
	for( auto& path : paths )
		asset_manager.importFile( path.string() );

}

void TopBar::exportFile( void )
{
	AssetManager asset_manager;
	auto         selection = asset_manager.getAssetSelection();
	if( selection.size() == 1 )
	{
		auto asset = asset_manager.getAsset( *selection.begin() );
		auto path = FileUtil::saveFileDialog( asset->getType() );
		const auto file_handle = FileUtil::open( path.string(), FileUtil::flags::WRITE_ONLY | FileUtil::flags::CREATE | FileUtil::flags::BINARY | FileUtil::flags::TRUNCATE, FileUtil::permissions::WRITE );
		FileUtil::write( file_handle, asset->getData(), asset->getDataSize() );
		FileUtil::close( file_handle );
	}
	else if( selection.size() > 1 )
	{
		auto path = FileUtil::saveFolderDialog();
		for( auto& asset_hash : selection )
		{
			auto asset = asset_manager.getAsset( asset_hash );
			auto local_path = path / StringUtil::format( "%s%s", asset->getName().c_str(), asset->getExtension().c_str() );
			const auto file_handle = FileUtil::open( local_path.string(), FileUtil::flags::WRITE_ONLY | FileUtil::flags::CREATE | FileUtil::flags::BINARY | FileUtil::flags::TRUNCATE, FileUtil::permissions::WRITE );
			FileUtil::write( file_handle, asset->getData(), asset->getDataSize() );
			FileUtil::close( file_handle );
		}
	}
	else
	{
		NotificationManager::addNotification( { "No asset selected to export" } );
	}
}
