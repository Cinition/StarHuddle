#pragma once

#include "File.h"

#include <map>
#include <string>

class FileManager
{

public:

	void loadFiles          ( void );
	void checkFiles         ( void );
	void importFiles        ( const std::string& _path );
	void exportFiles        ( void );
	void addFileSelection   ( size_t _hash, bool _clear_selection = true );
	void removeFileSelection( size_t _hash );

	const auto& getFileSelection( void ) const { return m_selected_files; }
	const auto& getFiles        ( void ) const { return m_files; }

private:

	uint8_t* load_file( const std::string& _path );

	static std::vector< size_t >    m_selected_files;
	static std::map< size_t, File > m_files;

};
