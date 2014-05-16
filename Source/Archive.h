/* Archive.h */
#pragma once

#include "predefine.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <direct.h>
#include <exception>
#include <new>          // std::bad_alloc

#include "Types.h"
#include "./Utils/FileUtils.h"
#include "./Utils/StringUtils.h"
#include "./Utils/DebugUtils.h"
#include "ArchiveComment.h"
#include "ArchiveHeader.h"
#include "ArchiveFile.h"
#include "ArchiveFileNameDesc.h"
#include "ArchiveFileNameChunk.h"
#include "ArchiveDirectoryNameDesc.h"
#include "ArchiveDirectoryNameChunk.h"
#include "ArchiveCompressedFileData.h"

#include "./Utils/Blast/blastHandler.h"

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
		bool parseStringChunk(ArchiveCompressedStringDesc& desc, ArchiveCompressedStringChunk& chunk, 
								char*& pCompressedBuffer, std::vector<wchar_t*>& outputVector);

		void open(char* szFilePath);
		void extractByIndex(uint32_t index);
		void extractAll();
		void close();

		// Header
		ArchiveComment m_Comment;
		ArchiveHeader m_Header;

		// Directory Name
		ArchiveDirectoryNameDesc m_DirectoryNameDesc;
		char* m_pCompressedDirectoryNameChunk;				// pointer to the raw(compressed) data from the h2o package
		ArchiveDirectoryNameChunk m_DirectoryNameChunk;
		std::vector<wchar_t*> m_DirectoryNameList;

		// File Name
		ArchiveFileNameDesc m_FileNameDesc;
		char* m_pCompressedFileNameChunk;					// pointer to the raw(compressed) data from the h2o package
		ArchiveFileNameChunk m_FileNameChunk;
		std::vector<wchar_t*> m_FileNameList;

		// Directory Structure
		uint32_t m_DirectoryCount;
		int32_t* m_arrDirectoryParents;
		
		// File
		std::vector<ArchiveFile> m_FileList;


	protected:
		std::ifstream m_hH2O;
	private:
		void init();
};
