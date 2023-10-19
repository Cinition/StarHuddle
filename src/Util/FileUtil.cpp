#include "FileUtil.h"

#include <io.h>
#include <direct.h>
#include <shobjidl.h>
#include <codecvt>

auto FileUtil::open( const std::string& _path, const uint32_t _flags, const uint32_t _mode ) -> const uint32_t
{
	return _open( _path.c_str(), _flags, _mode );
}

auto FileUtil::read( const uint32_t _file_handle, void* _data, const uint32_t _data_size ) -> const uint32_t
{
	return _read( _file_handle, _data, _data_size );
}

auto FileUtil::write( const uint32_t _file_handle, void* _data, const uint32_t _data_size ) -> const uint32_t
{
	return _write( _file_handle, _data, _data_size );
}

void FileUtil::close( const uint32_t _file_handle )
{
	_close( _file_handle );
}

auto FileUtil::openFileDialog( void ) -> std::vector< std::filesystem::path >
{
	std::vector< std::filesystem::path > paths;

	CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );

	IFileOpenDialog* file_dialog;
	IShellItem*      shell_item;
	IShellItemArray* shell_items;

	if( SUCCEEDED( CoCreateInstance( CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &file_dialog ) ) ) )
	{
		DWORD options;
		if( SUCCEEDED( file_dialog->GetOptions( &options ) ) )
			file_dialog->SetOptions( FOS_ALLOWMULTISELECT | options );

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

					paths.push_back( converted_string );

					CoTaskMemFree( file_path );
				}
				shell_item->Release();
			}
			else if( SUCCEEDED( file_dialog->GetResults( &shell_items ) ) )
			{
				DWORD file_count;
				shell_items->GetCount( &file_count );

				for( DWORD i = 0; i < file_count ; i++ )
				{
					PWSTR file_path;
					shell_items->GetItemAt( i, &shell_item );
					if( SUCCEEDED( shell_item->GetDisplayName( SIGDN_FILESYSPATH, &file_path ) ) )
					{
						std::wstring_convert< std::codecvt_utf8< wchar_t > > converter;
						
						auto wide_string      = std::wstring( file_path );
						auto converted_string = converter.to_bytes( wide_string );

						paths.push_back( converted_string );

						CoTaskMemFree( file_path );
					}
					shell_item->Release();
				}
				shell_items->Release();
			}
		}
		file_dialog->Release();
	}

	CoUninitialize();

	return paths;
}

auto FileUtil::saveFileDialog( Asset::Type _type ) -> std::filesystem::path
{
	std::filesystem::path path;

	CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );

	IFileSaveDialog* file_dialog;
	IShellItem*      shell_item;

	if( SUCCEEDED( CoCreateInstance( CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &file_dialog ) ) ) )
	{
		DWORD options;
		if( SUCCEEDED( file_dialog->GetOptions( &options ) ) )
			file_dialog->SetOptions( options );

		COMDLG_FILTERSPEC filter_spec{};

		if( _type == Asset::Type::JSON )
		{
			filter_spec.pszName = L"JavaScript Object Notation";
			filter_spec.pszSpec = L"*.json";

			file_dialog->SetDefaultExtension( L"json" );
		}
		else if( _type == Asset::Type::TGA )
		{
			filter_spec.pszName = L"Targa Graphics";
			filter_spec.pszSpec = L"*.tga";

			file_dialog->SetDefaultExtension( L"tga" );
		}
		else if( _type == Asset::Type::OGG )
		{
			filter_spec.pszName = L"OGG";
			filter_spec.pszSpec = L"*.ogg";

			file_dialog->SetDefaultExtension( L"ogg" );
		}

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

					path = converted_string;

					CoTaskMemFree( file_path );
				}
				shell_item->Release();
			}
		}

		file_dialog->Release();
	}

	CoUninitialize();

	return path;
}

auto FileUtil::saveFolderDialog() -> std::filesystem::path
{
	std::filesystem::path path;

	CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );

	IFileOpenDialog* file_dialog;
	IShellItem*      shell_item;

	if( SUCCEEDED( CoCreateInstance( CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &file_dialog ) ) ) )
	{
		DWORD options;
		if( SUCCEEDED( file_dialog->GetOptions( &options ) ) )
			file_dialog->SetOptions( FOS_PICKFOLDERS | options );

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

					path = converted_string;

					CoTaskMemFree( file_path );
				}
				shell_item->Release();
			}
		}

		file_dialog->Release();
	}

	CoUninitialize();

	return path;
}
