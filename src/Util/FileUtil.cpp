#include "FileUtil.h"

#include <io.h>
#include <direct.h>

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
