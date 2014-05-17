/* ArchiveComment.h */
#pragma once

#include "Types.h"
#include "Windows.h"
#include <exception>

#define H2O_COMMENT_TERMINATOR 0x1A

struct OuterException : std::exception{};

#pragma pack(push, 1)
struct ArchiveComment
{
	~ArchiveComment()
	{
		delete[] szComments;
	};
	char szHeader[8];
	float VersionInfo;
	char* szComments;
};
#pragma pack(pop)