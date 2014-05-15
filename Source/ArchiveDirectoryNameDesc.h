/* ArchiveDirectoryNameDesc.h */
#pragma once

#include "Types.h"

#pragma pack(push, 1)
struct ArchiveDirectoryNameDesc
{
	uint32_t CompressedSize;
	uint32_t RawSize;
	char CRC32[4];
};
#pragma pack(pop)