/* Archive.h */
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include "Types.h"
#include "DebugUtils.h"
#include "ArchiveComment.h"
#include "ArchiveHeader.h"

class Archive
{
	public:
		Archive();
		Archive(char* szFilePath);
		~Archive();

		uint64_t readComment(uint64_t streamPos);
		uint64_t readHeader(uint64_t streamPos);

		void open(char* szFilePath);
		void close();

		ArchiveComment m_Comment;
		ArchiveHeader m_Header;

	protected:
		std::ifstream m_hH2O;
	private:
		void init();
};
