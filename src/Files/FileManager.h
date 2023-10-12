#pragma once

#include "File.h"

#include <map>
#include <string>

class FileManager
{

public:

	void loadFiles          ( void );
	void checkFiles         ( void );
	void importFiles        ( void );
	void exportFiles        ( void );
	void addFileSelection   ( const std::string& _hash, bool _clear_selection = true );
	void removeFileSelection( const std::string& _hash );

	const std::vector< std::string >&    getFileSelection( void ) const { return m_selected_files; }
	const std::map< std::string, File >& getFiles        ( void ) const { return m_files; }

private:

	static std::vector< std::string >    m_selected_files;
	static std::map< std::string, File > m_files;

};

