/* Archive.h */
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <direct.h>

#include "Types.h"
#include "FileUtils.h"
#include "StringUtils.h"
#include "DebugUtils.h"
#include "ArchiveComment.h"
#include "ArchiveHeader.h"
#include "ArchiveFile.h"
#include "ArchiveFileNameDesc.h"
#include "ArchiveFileNameChunk.h"
#include "ArchiveFileName.h"

class Archive
{
	public:
		Archive();
		Archive(char* szFilePath);
		~Archive();

		uint64_t readComment(uint64_t streamPos);
		uint64_t readHeader(uint64_t streamPos);
		uint64_t readFileList(uint64_t streamPos);

		void open(char* szFilePath);
		void extractByIndex(uint32_t index);
		void extractAll();
		void close();

		ArchiveComment m_Comment;
		ArchiveHeader m_Header;
		std::vector<ArchiveFile> m_FileList;


	protected:
		std::ifstream m_hH2O;
	private:
		void init();
};
