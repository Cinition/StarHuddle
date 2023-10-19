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

	const auto& getHash     ( void ) const { return m_hash; }
	const auto& getName     ( void ) const { return m_name; }
	const auto& getType     ( void ) const { return m_type; }
	const auto& getIcon     ( void ) const { return m_texture; }
	const auto& getMetaData ( void ) const { return m_meta_data; }
	const auto& getData     ( void ) const { return m_data; }
	const auto& getDataSize ( void ) const { return m_data_size; }
	const auto getExtension( void ) const { return m_path.extension().string(); }

	friend void to_json( nlohmann::json& j, const Asset& v )
	{
		auto data = static_cast< uint8_t* >( v.getData() );
		auto vector_data = std::vector( &data[ 0 ], &data[ v.getDataSize() ] );

		j = nlohmann::json{
			{ "hash",      v.getHash() },
			{ "name",      v.getName() },
			{ "type",      ( uint32_t )v.getType() },
			{ "data",      vector_data },
			{ "data_size", v.getDataSize() },
		};
	}

protected:

	virtual void handleData( uint8_t* _data ) = 0;
	virtual void createMetaData( void ) = 0;

	size_t                  m_hash;
	std::string             m_name;
	Type                    m_type;
	Texture2D               m_texture;
	std::filesystem::path   m_path;
	std::vector< MetaData > m_meta_data;
	void*                   m_data;
	uint32_t                m_data_size;

};
