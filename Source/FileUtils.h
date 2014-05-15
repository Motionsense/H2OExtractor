/* FileUtils.h */
#pragma once

#include <io.h>			// For access()
#include <sys/types.h>	// For stat()
#include <sys/stat.h>	// For stat()
#include "Types.h"

enum PathType { TYPE_DIR, TYPE_FILE, TYPE_NOT_EXIST };
PathType checkPathType(const char* dirPath);