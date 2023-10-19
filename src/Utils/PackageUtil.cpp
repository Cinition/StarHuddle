#include "PackageUtil.h"

#include "Utils/FileUtil.h"

namespace PackageUtil
{
	void exportPackage( PackageHeader _header, PackageData _data )
	{
		const int32_t file_handle = FileUtil::open( "path", FileUtil::flags::WRITE_ONLY | FileUtil::flags::CREATE | FileUtil::flags::BINARY | FileUtil::flags::TRUNCATE, FileUtil::permissions::WRITE );
		FileUtil::write( file_handle, &_header, sizeof( PackageHeader ) );
		FileUtil::write( file_handle, &_data.json_data, _data.json_data_size );
		FileUtil::write( file_handle, &_data.tga_data, _data.tga_data_size );
		FileUtil::write( file_handle, &_data.ogg_data, _data.ogg_data_size );
		FileUtil::close( file_handle )
	}
}
