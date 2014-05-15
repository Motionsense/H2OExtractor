/* ArchiveComment.h */
#pragma once

#include "Types.h"

#define H2O_COMMENT_TERMINATOR 0x1A

#pragma pack(push, 1)
struct ArchiveComment
{
	char szHeader[8];
	float VersionInfo;
	char* szComments;
};
#pragma pack(pop)