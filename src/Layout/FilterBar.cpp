#include "FilterBar.h"

#include "Assets/AssetManager.h"

#include "UI/Style.h"

#include <Windows.h>
#include <shobjidl.h>
#include <codecvt>

FilterBar::FilterBar( Vector2& _cursor_position, Vector2 _size )
{
	float search_width = 870.f;
	float button_width = 200.f;
	float filter_width = _size.x - ( search_width + UI::MARGIN + button_width + UI::MARGIN );
	m_search = SearchElement( _cursor_position, Vector2( search_width, _size.y ) );
	_cursor_position.x += search_width + UI::MARGIN; 
	m_filter = FilterElement( _cursor_position, Vector2( filter_width, _size.y ) );
	_cursor_position.x += filter_width + UI::MARGIN; 
	m_package_button = Button( "Package", _cursor_position, Vector2( button_width, _size.y ), FilterBar::packageAssets );

}

void FilterBar::update()
{
	m_search.update();
	m_filter.update();
	m_package_button.tick();
}

void FilterBar::draw( void )
{
	m_search.draw();
	m_filter.draw();
	m_package_button.draw();
}

void FilterBar::packageAssets( void )
{
	// open windows dialog
	CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );

	IFileSaveDialog* file_dialog;
	IShellItem*      shell_item;

	if( SUCCEEDED( CoCreateInstance( CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &file_dialog ) ) ) )
	{
		DWORD options;
		if( SUCCEEDED( file_dialog->GetOptions( &options ) ) )
			file_dialog->SetOptions( options );

		COMDLG_FILTERSPEC filter_spec{};
		filter_spec.pszName = L"StarHuddle Package File";
		filter_spec.pszSpec = L"*.shp";

		file_dialog->SetDefaultExtension( L"shp" );
		file_dialog->SetFileTypes( 1, &filter_spec );

		if( SUCCEEDED( file_dialog->Show( NULL ) ) )
		{
			if( SUCCEEDED( file_dialog->GetResult( &shell_item ) ) )
			{
				PWSTR file_path;
				if( SUCCEEDED( shell_item->GetDisplayName( SIGDN_FILESYSPATH, &file_path ) ) )
				{
					std::wstring_convert< std::codecvt_utf8< wchar_t > > converter;
					
					auto wide_string      = std::wstring( file_path );
					auto converted_string = converter.to_bytes( wide_string );
					AssetManager::packageAssets( converted_string );

					CoTaskMemFree( file_path );
				}
				shell_item->Release();
			}
		}

		file_dialog->Release();
	}

	CoUninitialize();


}
