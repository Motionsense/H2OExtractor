/* ArchiveCompressedStringChunk.h */
#pragma once

#include "Types.h"

#pragma pack(push, 1)
struct ArchiveCompressedStringChunk
{
	uint32_t StringsCount;
	uint32_t ChunkSize;
};
#pragma pack(pop)