#pragma once

#include "json.hpp"

#include "raylib.h"

#include <vector>
#include <string>
#include <filesystem>

class Asset
{

public:

	enum class Type
	{
		JSON = 0,
		TGA = 1,
		OGG = 2,
	};

	struct MetaData
	{
		std::string name;
		std::string data;
	};

	const auto& getId       ( void ) const { return m_id; }
	const auto& getName     ( void ) const { return m_name; }
	const auto& getType     ( void ) const { return m_type; }
	const auto& getIcon     ( void ) const { return m_texture; }
	const auto& getMetaData ( void ) const { return m_meta_data; }
	const auto& getData     ( void ) const { return m_data; }
	const auto& getDataSize ( void ) const { return m_data_size; }
	const auto& getExtension( void ) const { return m_extension; }

protected:

	virtual void handleData( uint8_t* _data ) = 0;
	virtual void createMetaData( void ) = 0;

	uint32_t                m_id;
	std::string             m_name;
	std::string             m_extension;
	Type                    m_type;
	Texture2D               m_texture;
	std::vector< MetaData > m_meta_data;
	void*                   m_data;
	uint32_t                m_data_size;

};
