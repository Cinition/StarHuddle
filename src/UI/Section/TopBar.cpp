#include "TopBar.h"

#include "Manager/AssetManager.h"
#include "Manager/NotificationManager.h"
#include "UI/Layout.h"
#include "UI/Style.h"
#include "Util/FileUtil.h"
#include "Util/StringUtil.h"
#include "Util/PackageUtil.h"

#include <shtypes.h>

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
	AssetManager         asset_manager;
	PackageUtil::Package package;

	int package_size = 0;

	for( auto& asset : asset_manager.getAssets() )
	{
		auto& asset_value = asset.second;
		if( asset_value->getType() == Asset::Type::JSON )
		{
			package.json.push_back( { asset_value->getData(), asset_value->getDataSize(), asset_value->getName() } );
			package.header.json_count += 1;
		}
		else if( asset_value->getType() == Asset::Type::TGA )
		{
			package.tga.push_back( { asset_value->getData(), asset_value->getDataSize(), asset_value->getName() } );
			package.header.tga_count += 1;
		}
		else if( asset_value->getType() == Asset::Type::OGG )
		{
			package.ogg.push_back( { asset_value->getData(), asset_value->getDataSize(), asset_value->getName() } );
			package.header.ogg_count += 1;
		}	
		// MARKER: File Format Combination

		package_size += asset_value->getDataSize();
	}

	package.header.package_size = package_size;

	COMDLG_FILTERSPEC filter_spec{};
	filter_spec.pszName = L"Starhuddle Asset Package";
	filter_spec.pszSpec = L"*.shp";
	LPCWSTR extension   = { L"shp" };

	auto path = FileUtil::saveFileDialog( filter_spec, extension );

	PackageUtil::exportPackage( package, path.string() );
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

		COMDLG_FILTERSPEC filter_spec{};
		LPCWSTR           extension{};
		if( asset->getType() == Asset::Type::JSON )
		{
			filter_spec.pszName = L"JavaScript Object Notation";
			filter_spec.pszSpec = L"*.json";
			extension           = L"json";
		}
		else if( asset->getType() == Asset::Type::TGA )
		{
			filter_spec.pszName = L"Truevision Graphics";
			filter_spec.pszSpec = L"*.tga";
			extension           = L"tga";
		}
		else if( asset->getType() == Asset::Type::OGG )
		{
			filter_spec.pszName = L"OGG";
			filter_spec.pszSpec = L"*.ogg";
			extension           = L"ogg";
		}
		// MARKER: File Format Exporting

		auto path = FileUtil::saveFileDialog( filter_spec, extension );
		const auto file_handle = FileUtil::open( path.string(), FileUtil::flags::WRITE_ONLY | FileUtil::flags::CREATE | FileUtil::flags::BINARY | FileUtil::flags::TRUNCATE, FileUtil::permissions::WRITE );
		FileUtil::write( file_handle, asset->getData(), asset->getDataSize() );
		FileUtil::close( file_handle );
	}
	else if( selection.size() > 1 )
	{
		auto path = FileUtil::saveFolderDialog();
		for( auto& id : selection )
		{
			auto asset = asset_manager.getAsset( id );
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
