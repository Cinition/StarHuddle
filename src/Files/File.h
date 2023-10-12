#pragma once

#include <vector>
#include <string>
#include <filesystem>

class File
{

public:

	enum class Type
	{
		JSON = 1,
		TGA = 2,
		OGG = 3,
		WAV = 4,
	};

	File( const std::filesystem::path& _path, uint8_t* _data )
	{
		handleData( _data );
		createMetaData();
	}

	const auto& getName    ( void ) const { return m_name; }
	const auto& getType    ( void ) const { return m_type; }
	const auto& getHash    ( void ) const { return m_hash; }
	const auto& getMetaData( void ) const { return m_meta_data; }

protected:

	virtual void handleData( uint8_t* ) = 0;
	virtual void createMetaData( void ) = 0;

	size_t                     m_hash;
	std::string                m_name;
	Type                       m_type;
	std::filesystem::path      m_path;
	std::vector< std::string > m_meta_data;

};
