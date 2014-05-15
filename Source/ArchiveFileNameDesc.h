/* ArchiveFileNameDesc.h */
#pragma once

#include "Types.h"

#pragma pack(push, 1)
struct ArchiveFileNameDesc
{
	uint32_t CompressedSize;
	uint32_t RawSize;
	char CRC32[4];
	char* CompressedChunk;
};
#pragma pack(pop)