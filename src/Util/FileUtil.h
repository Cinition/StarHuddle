#pragma once

#include <stdint.h>
#include <string>
#include <fcntl.h>

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
		constexpr uint32_t APPEND     = _O_APPEND;
		constexpr uint32_t CREATE     = _O_CREAT;
		constexpr uint32_t TRUNCATE   = _O_TRUNC;
		constexpr uint32_t TEXT       = _O_TEXT;
		constexpr uint32_t BINARY     = _O_BINARY;
	}

	auto open( const std::string& _path, const uint32_t _flags, const uint32_t _mode ) -> const uint32_t;
	auto read( const uint32_t _file_handle, void* _data, const uint32_t _data_size ) -> const uint32_t;
	auto write( const uint32_t _file_handle, void* _data, const uint32_t _data_size ) -> const uint32_t;
	void close( const uint32_t _file_handle );
}
