/* ArchiveFileName.h */
#pragma once

#include "Types.h"

#pragma pack(push, 1)
struct ArchiveFileName
{
	char* FileName;
	uint16_t NullTerminator;
};	
#pragma pack(pop)
