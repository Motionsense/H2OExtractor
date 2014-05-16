/* ArchiveHeader.h */
#pragma once

#include "Types.h"

#pragma pack(push, 1)
struct ArchiveHeader
{
	uint32_t Version;
	uint32_t FileCount;		// may not be accurate due to empty entries
	uint64_t CompressedSize;
	uint64_t RawSize;
};
#pragma pack(pop)