/* FileUtils.h */
#pragma once

#include <io.h>			// For access()
#include <sys/types.h>	// For stat()
#include <sys/stat.h>	// For stat()
#include <string>

#include "./dirent/dirent.h"
#include "../Types.h"

namespace Util { namespace File {
	enum PathType { TYPE_DIR, TYPE_FILE, TYPE_NOT_EXIST };
	PathType checkPathType(const char* dirPath);
}}
