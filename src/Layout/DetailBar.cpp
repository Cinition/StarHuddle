#include "DetailBar.h"

#include "Assets/AssetManager.h"
#include "UI/Style.h"

#include <Windows.h>
#include <shobjidl.h>

DetailBar::DetailBar( Vector2& _cursor_position, Vector2 _size )
: UIElement( _cursor_position, _size )
{
	Vector2 button_size = Vector2( m_position.x + UI::MARGIN, m_position.y + UI::MARGIN + m_inner_size.y - 40.f );
	m_export_button     = Button( "Export", button_size, Vector2( m_inner_size.x, 40.f ), DetailBar::exportFile );
}

void DetailBar::update(void)
{
	m_export_button.tick();
}

void DetailBar::drawNoSelection( void )
{
	int         font_size = 12;
	std::string text      = "No assets selected";

	RaylibDrawText( text.c_str(), ( m_position.x + UI::MARGIN + ( ( m_inner_size.x - MeasureText( text.c_str(), font_size ) ) / 2 ) ), m_position.y + ( ( m_inner_size.y - font_size ) / 2 ), font_size, UI::TEXT_COLOR );
}

void DetailBar::drawAssetDetail( void )
{
	auto asset = AssetManager::getAsset( AssetManager::getAssetSelection().back() );
	if( !asset )
		return;

	Vector2 cursor_position = Vector2Add( m_position, Vector2( UI::MARGIN, UI::MARGIN ) );

	// draw Icon
	Texture2D asset_texture{};
	switch( asset->getType() )
	{
		case Asset::Type::JSON: asset_texture = LoadTexture( "../data/textures/JSON.png" ); break;
		case Asset::Type::TGA: asset_texture = LoadTexture( "../data/textures/TGA.png" ); break;
		case Asset::Type::OGG: asset_texture = LoadTexture( "../data/textures/OGG.png" ); break;
	}

	drawAssetIcon( cursor_position, asset_texture );
	cursor_position.y += UI::MARGIN;

	drawAssetName( cursor_position, asset->getName() );
	cursor_position.y += UI::MARGIN / 2;

	DrawRectangle( cursor_position.x, cursor_position.y, m_inner_size.x, 4, UI::PRIMARY );
	cursor_position.y += 4 + UI::MARGIN / 2;

	for( auto& meta_data : asset->getMetaData() )
		drawMetaData( cursor_position, meta_data );

}

void DetailBar::drawAssetIcon( Vector2& _cursor_position, Texture2D _icon )
{
	RaylibRectangle texture_rect;
	texture_rect.x = 0.f;
	texture_rect.y = 0.f;
	texture_rect.width = _icon.width;
	texture_rect.height = _icon.height;

	RaylibRectangle rect;
	rect.x = _cursor_position.x + ( m_inner_size.x - texture_rect.width ) / 2;
	rect.y = _cursor_position.y;
	rect.width = texture_rect.width;
	rect.height = texture_rect.height;

	DrawTexturePro( _icon, texture_rect, rect, { 0.f, 0.f }, 0.f, WHITE );
	_cursor_position.y += texture_rect.height;
}

void DetailBar::drawAssetName( Vector2& _cursor_position, const std::string& _text )
{
	int     font_size  = 16;
	int     text_width = MeasureText( _text.c_str(), font_size );
	Vector2 text_pos   = Vector2( _cursor_position.x + ( m_inner_size.x - text_width ) / 2, _cursor_position.y );
	RaylibDrawText( _text.c_str(), text_pos.x, text_pos.y, font_size, UI::TEXT_COLOR );
	_cursor_position.y += font_size;
}

void DetailBar::drawMetaData( Vector2& _cursor_position, const Asset::MetaData& _meta_data )
{
	int     font_size        = 12;
	int     _name_width      = MeasureText( _meta_data.name.c_str(), font_size );
	int     _data_width      = MeasureText( _meta_data.data.c_str(), font_size );
	Vector2 _name_pos        = Vector2( _cursor_position.x, _cursor_position.y );
	Vector2 _data_pos        = Vector2( _cursor_position.x + m_inner_size.x - _data_width, _cursor_position.y );

	RaylibDrawText( _meta_data.name.c_str(), _name_pos.x, _name_pos.y, font_size, UI::TEXT_COLOR );
	RaylibDrawText( _meta_data.data.c_str(), _data_pos.x, _data_pos.y, font_size, UI::TEXT_COLOR );

	_cursor_position.y += font_size;
}

void DetailBar::drawInner( Vector2 _cursor_position )
{
	AssetManager asset_manager;
	if( asset_manager.getAssetSelection().empty() )
		drawNoSelection();
	else
		drawAssetDetail();

	m_export_button.draw();
}

void DetailBar::exportFile( void )
{
	AssetManager asset_manager;
	if( asset_manager.getAssetSelection().empty() )
		return; // can't export with no asset selected

	// open windows dialog
	std::filesystem::path path = std::filesystem::current_path();
	char                  file_path_buffer[ 2048 ]{};

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
						auto wide_string = std::wstring( file_path );
						auto converted_string = std::string( wide_string.begin(), wide_string.end() );
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
