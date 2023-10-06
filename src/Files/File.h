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

	virtual std::string getName(void) const = 0;
	virtual Type getType(void) const = 0;
	auto getHash(void) const { return m_hash; }
	auto getMetaData(void) const { return m_meta_data; }

protected:

	virtual void setupHash(void) = 0;
	virtual void setupPath(void) = 0;
	virtual void setupMetaData(void) = 0;

private:

	std::string m_hash;
	std::filesystem::path m_path;
	std::vector< std::string > m_meta_data;

};
