#pragma once

#include <vector>
#include <string>
#include <filesystem>

class File
{

public:

	enum class Type
	{
		JSON = 0,
		TGA = 1,
		OGG = 2,
	};

	const auto& getName    ( void ) const { return m_name; }
	const auto& getType    ( void ) const { return m_type; }
	const auto& getHash    ( void ) const { return m_hash; }
	const auto& getMetaData( void ) const { return m_meta_data; }

protected:

	virtual void handleData( uint8_t* _data ) = 0;
	virtual void createMetaData( void ) = 0;

	size_t                     m_hash;
	std::string                m_name;
	Type                       m_type;
	std::filesystem::path      m_path;
	std::vector< std::string > m_meta_data;

};
