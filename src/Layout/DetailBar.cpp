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

void DetailBar::drawInner( Vector2 _cursor_position )
{
	m_export_button.draw();
}

void DetailBar::exportFile( void )
{
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
					AssetManager asset_manager;
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
