/* ArchiveFileNameChunk.h */
#pragma once

#include "Types.h"

#pragma pack(push, 1)
struct ArchiveFileNameChunk
{
	uint32_t FileNameCount;
	uint32_t FileNameSize;
};
#pragma pack(pop)