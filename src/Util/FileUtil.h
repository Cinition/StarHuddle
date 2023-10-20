#pragma once

#include "Asset/Asset.h"

#include <stdint.h>
#include <string>
#include <fcntl.h>
#include <vector>
#include <filesystem>
#include <shtypes.h>

namespace FileUtil
{
	namespace permissions
	{
		constexpr uint32_t READ  = _S_IREAD;
		constexpr uint32_t WRITE = _S_IWRITE;
	}

	namespace flags
	{
		constexpr uint32_t READ_ONLY  = _O_RDONLY;
		constexpr uint32_t WRITE_ONLY = _O_WRONLY;
		constexpr uint32_t TEMPORARY  = _O_TEMPORARY;
		constexpr uint32_t APPEND     = _O_APPEND;
		constexpr uint32_t CREATE     = _O_CREAT;
		constexpr uint32_t TRUNCATE   = _O_TRUNC;
		constexpr uint32_t TEXT       = _O_TEXT;
		constexpr uint32_t BINARY     = _O_BINARY;
	}

	auto open( const std::string& _path, const uint32_t _flags, const uint32_t _mode ) -> const uint32_t;
	auto read( const uint32_t _file_handle, void* _data, const uint32_t _data_size ) -> const uint32_t;
	auto write( const uint32_t _file_handle, void* _data, const uint32_t _data_size ) -> const uint32_t;
	auto seek( const uint32_t _file_handle, uint32_t _offset, uint32_t _origin ) -> const uint32_t;
	void close( const uint32_t _file_handle );

	auto openFileDialog( void ) -> std::vector< std::filesystem::path >;
	auto saveFileDialog( COMDLG_FILTERSPEC _filter, LPCWSTR _extension ) -> std::filesystem::path;
	auto saveFolderDialog() -> std::filesystem::path;
}
