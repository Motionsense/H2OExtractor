/* ArchiveFile.h */
#pragma once

#include "Types.h"

#pragma pack(push, 1)
struct ArchiveFile
{
	uint32_t CompressionTag;
	int32_t FolderNameIndex;
	int32_t FileNameIndex;
	uint32_t FileId;
	uint32_t RawSize;
	uint32_t CompressedSize;
	uint64_t Offest;
	char CRC32[4];
	uint32_t UnknownConstant;
};
#pragma pack(pop)