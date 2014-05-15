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
#include "ArchiveDirectoryNameDesc.h"

class Archive
{
	public:
		Archive();
		Archive(char* szFilePath);
		~Archive();

		uint64_t readComment(uint64_t streamPos);
		uint64_t readHeader(uint64_t streamPos);
		uint64_t readFileList(uint64_t streamPos);
		uint64_t readFileNameDesc(uint64_t streamPos);
		uint64_t readFileNameChunk(uint64_t streamPos);
		uint64_t readDirectoryNameDesc(uint64_t streamPos);
		uint64_t readDirectoryNameChunk(uint64_t streamPos);
		uint64_t readDirectoryParents(uint64_t streamPos);

		void open(char* szFilePath);
		void extractByIndex(uint32_t index);
		void extractAll();
		void close();

		ArchiveComment m_Comment;
		ArchiveHeader m_Header;
		ArchiveFileNameDesc m_FileNameDesc;
		ArchiveDirectoryNameDesc m_DirectoryNameDesc;
		uint32_t m_DirectoryCount;
		int32_t* m_aDirectoryParents;

		char* m_pFileNameChunk;			// pointer the raw(compressed) data from the h2o package
		char* m_pDirectoryNameChunk;	// pointer the raw(compressed) data from the h2o package
		std::vector<ArchiveFile> m_FileList;


	protected:
		std::ifstream m_hH2O;
	private:
		void init();
};
