#include "AssetDetail.h"

#include "Manager/AssetManager.h"
#include "UI/Style.h"
#include "UI/Layout.h"
#include "Util/UIUtil.h"

/*
#include <Windows.h>
#include <shobjidl.h>
#include <codecvt>

void DetailBar::exportFile( void )
{
	AssetManager asset_manager;
	if( asset_manager.getAssetSelection().empty() )
		return; // can't export with no asset selected

	// open windows dialog
	CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );

	IFileDialog* file_dialog;
	IShellItem*  shell_item;

	if( SUCCEEDED( CoCreateInstance( CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &file_dialog ) ) ) )
	{
		DWORD options;
		if( SUCCEEDED( file_dialog->GetOptions( &options ) ) )
			file_dialog->SetOptions( options | FOS_PICKFOLDERS );

		if( SUCCEEDED( file_dialog->Show( NULL ) ) )
		{
			if( SUCCEEDED( file_dialog->GetResult( &shell_item ) ) )
			{
				PWSTR file_path;
				if( SUCCEEDED( shell_item->GetDisplayName( SIGDN_FILESYSPATH, &file_path ) ) )
				{
					for( auto& selected_asset_hash : asset_manager.getAssetSelection() )
					{
						std::wstring_convert< std::codecvt_utf8< wchar_t > > converter;
						
						auto wide_string      = std::wstring( file_path );
						auto converted_string = converter.to_bytes( wide_string );
						asset_manager.exportAsset( selected_asset_hash, converted_string );
					}
					CoTaskMemFree( file_path );
				}
				shell_item->Release();
			}
		}

		file_dialog->Release();
	}

	CoUninitialize();
}
*/

AssetDetail::AssetDetail( const Vector2& _position, const Vector2& _size )
: UIElement( _position, _size )
{
}

void AssetDetail::update( const float /*_tick*/ )
{
}

void AssetDetail::draw( void )
{
	UIUtil::drawBackground( m_position, m_size, UI::GRADIENT1 );

	AssetManager asset_manager;
	if( asset_manager.getAssetSelection().empty() )
		drawEmptyDetail();
	else
		drawAssetDetail();
}

void AssetDetail::drawAssetDetail( void )
{
	AssetManager asset_manager;
	auto         asset_hash = *asset_manager.getAssetSelection().begin();
	auto         asset      = asset_manager.getAsset( asset_hash );
	if( !asset )
		return;

	Vector2 inner_size = Vector2Subtract( m_size, Vector2( UI::MARGIN * 2, UI::MARGIN * 2 ) );
	UIUtil::drawTexture( LAYOUT::ASSETDETAIL::ASSET_ICON_POS, LAYOUT::ASSETDETAIL::ASSET_ICON_SIZE, asset->getIcon() );
	UIUtil::drawTextCentered( asset->getName().c_str(), Vector2Add( m_position, Vector2( 0.f, LAYOUT::ASSETDETAIL::ASSET_ICON_SIZE.y + UI::MARGIN ) ), inner_size.x, 16, UI::TEXT_COLOR );
	
	Vector2 cursor_position = Vector2Add( LAYOUT::ASSETDETAIL::ASSET_ICON_POS, Vector2( 0.f, LAYOUT::ASSETDETAIL::ASSET_ICON_SIZE.y + UI::MARGIN / 2 ) );
	drawHorizontalLine( cursor_position );
	cursor_position.y += UI::MARGIN / 2;

	for( auto& meta_data : asset->getMetaData() )
		drawMetaData( meta_data, cursor_position );

}

void AssetDetail::drawEmptyDetail( void )
{
	int     font_size  = 12;
	Vector2 inner_size = Vector2Subtract( m_size, Vector2( UI::MARGIN * 2, UI::MARGIN * 2 ) );
	Vector2 text_pos   = Vector2Add( m_position, Vector2( UI::MARGIN, ( m_size.y - font_size ) / 2 ) );
	UIUtil::drawTextCentered( "No assets selected", text_pos, inner_size.x, font_size, UI::TEXT_COLOR );
}

void AssetDetail::drawHorizontalLine( Vector2& _cursor_position )
{
	_cursor_position.y += UI::MARGIN / 2;
	DrawRectangle( static_cast< int >( _cursor_position.x ), static_cast< int >( _cursor_position.y ), static_cast< int >( m_size.x - UI::MARGIN * 2 ), 4, UI::PRIMARY );
}

void AssetDetail::drawMetaData( const Asset::MetaData& _meta_data, Vector2& _cursor_position )
{
	int     font_size       = 12;
	int     data_width      = MeasureText( _meta_data.data.c_str(), font_size );
	Vector2 inner_size      = Vector2Subtract( m_size, Vector2( UI::MARGIN * 2, UI::MARGIN * 2 ) );
	Vector2 name_pos        = Vector2( _cursor_position.x, _cursor_position.y );
	Vector2 data_pos        = Vector2( _cursor_position.x + inner_size.x - data_width, _cursor_position.y );

	RaylibDrawText( _meta_data.name.c_str(), static_cast< int >( name_pos.x ), static_cast< int >( name_pos.y ), font_size, UI::TEXT_COLOR );
	RaylibDrawText( _meta_data.data.c_str(), static_cast< int >( data_pos.x ), static_cast< int >( data_pos.y ), font_size, UI::TEXT_COLOR );

	_cursor_position.y += static_cast< float >( font_size );
}

