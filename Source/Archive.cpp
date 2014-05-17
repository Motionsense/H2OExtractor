/* Archive.cpp */
#include "Archive.h"

Archive::Archive()
{
	init();
}

Archive::Archive(char* szFilePath)
{
	init();
	open(szFilePath);
}

Archive::~Archive()
{
	close();
	SAFE_DELETE_ARRAY(m_arrDirectoryParents);
	SAFE_DELETE_ARRAY(m_pCompressedFileNameChunk);
	SAFE_DELETE_ARRAY(m_pCompressedDirectoryNameChunk);
	Util::Gen::clearVectorOfArray(m_DirectoryNameList);
	Util::Gen::clearVectorOfArray(m_FileNameList);
}

uint64_t Archive::readComment(uint64_t streamPos)
{
	m_hH2O.seekg(streamPos, std::ios::beg);

	// Read Header
	m_hH2O.read(m_Comment.szHeader, 8);
	// Read VersionInfo
	m_hH2O.read((char*)&m_Comment.VersionInfo, 4);
	// Read Comments
	uint64_t beg = m_hH2O.tellg();
	char curByte = 0x0;
	while (!m_hH2O.eof() && curByte!=H2O_COMMENT_TERMINATOR)
	{
		m_hH2O.read(&curByte, 1);
	}
	uint64_t end = m_hH2O.tellg();
	m_hH2O.seekg(beg);
	uint64_t length = end-beg;
	m_Comment.szComments = new char[length];
	memset(m_Comment.szComments, 0, length);
	m_hH2O.read(m_Comment.szComments, length-1);

#ifdef H2O_DEBUG_LOG
	DB::debugLog("- ArchiveHeader: ", m_Comment.szHeader, NULL);
	DB::debugLog("- VersionInfo: ", m_Comment.VersionInfo, NULL);
	DB::debugLog("- Comments: ", m_Comment.szComments, NULL);
#endif
	return end;
}

uint64_t Archive::readHeader(uint64_t streamPos)
{
	m_hH2O.seekg(streamPos, std::ios::beg);
	m_hH2O.read((char*)&m_Header, sizeof(ArchiveHeader));

#ifdef H2O_DEBUG_LOG
	DB::debugLog("- Version: ", m_Header.Version, NULL);
	DB::debugLog("- FileCount: ", m_Header.FileCount, NULL);
	DB::debugLog("- CompressedSize: ", m_Header.CompressedSize, NULL);
	DB::debugLog("- RawSize: ", m_Header.RawSize, NULL);
#endif
	return m_hH2O.tellg();
}

uint64_t Archive::readFileList(uint64_t streamPos)
{
	m_hH2O.seekg(streamPos, std::ios::beg);
	ArchiveFile curFile;
	for (int i=0; i<m_Header.FileCount; i++)
	{
		m_hH2O.read((char*)&curFile, sizeof(ArchiveFile));
		if (curFile.RawSize!=0 && curFile.CompressedSize!=0)
			m_FileList.push_back(curFile);	// file is valid

	#if defined(H2O_DEBUG_LOG) && defined (H2O_PRINT_FILE_DESC)
		DB::debugLog("- CompressionTag: ", curFile.CompressionTag, NULL);
		DB::debugLog("- FolderNameIndex: ", curFile.FolderNameIndex, NULL);
		DB::debugLog("- FileNameIndex: ", curFile.FileNameIndex, NULL);
		DB::debugLog("- FileId: ", curFile.FileId, NULL);
		DB::debugLog("- RawSize: ", curFile.RawSize, NULL);
		DB::debugLog("- CompressedSize: ", curFile.CompressedSize, NULL);
		DB::debugLog("- Offest: ", curFile.Offest, NULL);
		DB::debugLog("- CRC32[hex]: ", curFile.CRC32, NULL, true);
		DB::debugLog("- UnknownConstant: ", curFile.UnknownConstant, NULL);
		DB::debugLog("-------------------", "", NULL);
	#endif
	}
	return m_hH2O.tellg();
}

uint64_t Archive::readFileNameDesc(uint64_t streamPos)
{
	m_hH2O.seekg(streamPos, std::ios::beg);
	m_hH2O.read((char*)&m_FileNameDesc, sizeof(ArchiveFileNameDesc));

	#ifdef H2O_DEBUG_LOG
		DB::debugLog("- CompressedSize: ", m_FileNameDesc.CompressedSize, NULL);
		DB::debugLog("- RawSize: ", m_FileNameDesc.RawSize, NULL);
		DB::debugLog("- CRC32[hex]: ", m_FileNameDesc.CRC32, NULL, true);
	#endif
	return m_hH2O.tellg();
}

uint64_t Archive::readFileNameChunk(uint64_t streamPos)
{
	m_hH2O.seekg(streamPos, std::ios::beg);
	m_pCompressedFileNameChunk = new char[m_FileNameDesc.CompressedSize];
	m_hH2O.read(m_pCompressedFileNameChunk, m_FileNameDesc.CompressedSize);
	// TODO: Decompress the file name chunk
	return m_hH2O.tellg();
}

uint64_t Archive::readDirectoryNameDesc(uint64_t streamPos)
{
	m_hH2O.seekg(streamPos, std::ios::beg);
	m_hH2O.read((char*)&m_DirectoryNameDesc, sizeof(ArchiveDirectoryNameDesc));

	#ifdef H2O_DEBUG_LOG
		DB::debugLog("- CompressedSize: ", m_DirectoryNameDesc.CompressedSize, NULL);
		DB::debugLog("- RawSize: ", m_DirectoryNameDesc.RawSize, NULL);
		DB::debugLog("- CRC32[hex]: ", m_DirectoryNameDesc.CRC32, NULL, true);
	#endif
	return m_hH2O.tellg();
}

uint64_t Archive::readDirectoryNameChunk(uint64_t streamPos)
{
	m_hH2O.seekg(streamPos, std::ios::beg);
	m_pCompressedDirectoryNameChunk = new char[m_DirectoryNameDesc.CompressedSize];
	m_hH2O.read(m_pCompressedDirectoryNameChunk, m_DirectoryNameDesc.CompressedSize);
	// TODO: Decompress the file name chunk
	return m_hH2O.tellg();
}

uint64_t Archive::readDirectoryParents(uint64_t streamPos)
{
	m_hH2O.seekg(streamPos, std::ios::beg);
	m_hH2O.read((char*)&m_DirectoryCount, sizeof(m_DirectoryCount));
	m_arrDirectoryParents = new int32_t[m_DirectoryCount];
	m_hH2O.read((char*)m_arrDirectoryParents, sizeof(*m_arrDirectoryParents)*m_DirectoryCount);

#ifdef H2O_DEBUG_LOG
	DB::debugLog("Directory Count: ", m_DirectoryCount, NULL);
	#ifdef H2O_PRINT_DIR_INHEIRTANCY
		for (int i=0; i<m_DirectoryCount; i++)
		{
			DB::debugLog("-> ", *(m_arrDirectoryParents), "");
		}
	#endif
#endif
	return m_hH2O.tellg();
}

bool Archive::parseStringChunk(ArchiveCompressedStringDesc& desc, ArchiveCompressedStringChunk& chunk,
							   char*& pCompressedBuffer, std::vector<wchar_t*>& outputVector)
{
	// Decompress
	char* pDecompressedBuffer = new char[desc.RawSize];
	bool result = runblast_mem2mem(pCompressedBuffer, desc.RawSize, pDecompressedBuffer, *(uint32_t*)(desc.CRC32));

	// Serialize the header of the chunk
	memcpy(&chunk, pDecompressedBuffer, sizeof(chunk));
	
	// Serialize the file names
	//outputVector.clear();
	uint32_t length = 0;
	uint32_t offest = sizeof(chunk);
	while (offest < desc.RawSize)
	{
		wchar_t* wszStartingPos = (wchar_t*)&pDecompressedBuffer[offest];
		length = wcslen(wszStartingPos);
		if (length==0)
			break;
		wchar_t* wszString = new wchar_t[length+1];
		wcscpy(wszString, wszStartingPos);
		outputVector.push_back(wszString);
		offest += length*sizeof(wchar_t) + 2;	// plus the length of null teminator
	}
	delete[] pDecompressedBuffer;
	return result;
}

void Archive::open(char* szFilePath)
{
	m_hH2O.open(szFilePath, std::ifstream::binary);

	uint64_t curPos = 0;
	DB::debugLog("Comment Section: ", "", NULL);
	curPos = readComment(curPos);
	DB::debugLog("Header Section: ", "", NULL);
	curPos = readHeader(curPos);
	DB::debugLog("\nFile Section: ", "", NULL);
	curPos = readFileList(curPos);

	DB::debugLog("\nDirectoryNameDesc Section: ", "", NULL);
	curPos = readDirectoryNameDesc(curPos);
	curPos = readDirectoryNameChunk(curPos);

	DB::debugLog("\nFileNameDesc Section: ", "", NULL);
	curPos = readFileNameDesc(curPos);
	curPos = readFileNameChunk(curPos);

	DB::debugLog("\nDirectoryParents Section: ", "", NULL);
	curPos = readDirectoryParents(curPos);

	bool success;
	// Parse compressed file names
	success = parseStringChunk(m_FileNameDesc, m_FileNameChunk, m_pCompressedFileNameChunk, m_FileNameList);
#ifdef H2O_DEBUG_LOG
	if (success)
		DB::debugLog("\nFileNameChunk - decompress: ", "Success!", "");
	else
		DB::debugLog("\nFileNameChunk - decompress: ", "Fail!", "");
	DB::debugLog("FileNameCount: ", m_FileNameChunk.StringsCount, "");
	DB::debugLog("ChunkSize: ", m_FileNameChunk.ChunkSize, "");
	#ifdef H2O_PRINT_FILE_LIST
		DB::debugLog("FileNames: ", "", "");
		for (int i=0; i<m_FileNameList.size(); i++)
		{
			std::wcout << m_FileNameList[i] << std::endl;
		}
		DB::debugLog("---------------", "", "");
	#endif
#endif

	// Parse compressed directory names
	success = parseStringChunk(m_DirectoryNameDesc, m_DirectoryNameChunk, m_pCompressedDirectoryNameChunk, m_DirectoryNameList);
#ifdef H2O_DEBUG_LOG
	if (success)
		DB::debugLog("\nDirectoryNameChunk - decompress: ", "Success!", "");
	else
		DB::debugLog("\nDirectoryNameChunk - decompress: ", "Fail!", "");
	DB::debugLog("DirectoryNameCount: ", m_DirectoryNameChunk.StringsCount, "");
	DB::debugLog("ChunkSize: ", m_DirectoryNameChunk.ChunkSize, "");
	#ifdef H2O_PRINT_FILE_LIST
		DB::debugLog("DirectoryNames: ", "", "");
		for (int j=0; j<m_DirectoryNameList.size(); j++)
		{
			std::wcout << m_DirectoryNameList[j] << std::endl;
		}
		DB::debugLog("---------------", "", "");
	#endif
#endif
	

}

// TODO: Refactor this function.
void Archive::extractByIndex(uint32_t index)
{
	//
	// Generate File Name
	//
	// TODO: Add folder structure
	char fileName[128];
	memset(fileName, 0, 128);
	if (m_FileList[index].FileNameIndex==-1)
	{
		getFileName(index, "", fileName);
	}
	else
	{
		wtoc(m_FileNameList[index], fileName);
	}
	char fullPath[256];
	getFullPath("output/", fileName, fullPath);
#ifdef H2O_PRINT_WHEN_EXTRACT
	DB::debugLog(fileName, "", "");
#endif

	//
	// Extract File
	//
	ArchiveFile& rFile = m_FileList[index];
	char* pFileBuffer;
	m_hH2O.seekg(rFile.Offest, std::ios::beg);

	// Decompress buffer if compressed
	if (rFile.CompressionTag!=0)
	{
		ArchiveCompressedFileData tFileDesc;
		m_hH2O.read((char*)&tFileDesc, sizeof(ArchiveCompressedFileData));
	#ifdef H2O_PRINT_WHEN_EXTRACT
		DB::debugLog("- CompressedSize: ", tFileDesc.CompressedSize, "");
		DB::debugLog("- RawSize: ", tFileDesc.RawSize, "");
		DB::debugLog("- CRC32[hex]: ", tFileDesc.CRC32, NULL, true);
	#endif
		pFileBuffer = new char[rFile.CompressedSize];
		m_hH2O.read(pFileBuffer, rFile.CompressedSize);
		char* pDecompressedBuffer = new char[tFileDesc.RawSize];
		bool result = runblast_mem2mem(pFileBuffer, tFileDesc.RawSize, pDecompressedBuffer, *(uint32_t*)(tFileDesc.CRC32));
		if (result)
		{
		#ifdef H2O_PRINT_WHEN_EXTRACT
			DB::debugLog("- Decompress: ", "Success!", " - output decompressed data");
		#endif
			delete[] pFileBuffer;	// delete the compressed buffer since we don't need it anymore
			pFileBuffer = pDecompressedBuffer;
		}
		else
		{
		#ifdef H2O_PRINT_WHEN_EXTRACT
			DB::debugLog("- Decompress: ", "Fail!", " - output compressed data");
		#endif
			delete[] pDecompressedBuffer;
		}
		pDecompressedBuffer = NULL;
	}
	else
	{
		pFileBuffer = new char[rFile.CompressedSize];
		m_hH2O.read(pFileBuffer, rFile.CompressedSize);
	}

	// write file
	std::ofstream destFile;
	destFile.open(fullPath, std::ofstream::binary);
	destFile.write(pFileBuffer, rFile.CompressedSize);
	destFile.close();
	
	delete[] pFileBuffer;
	pFileBuffer = NULL;
}

void Archive::extractAll()
{
	const char* dirPath = "output/";
	if (Util::File::checkPathType(dirPath)!=Util::File::TYPE_DIR)
		mkdir(dirPath);

	for (int i=0; i<m_FileList.size(); i++)	//m_Header.FileCount
	{
		extractByIndex(i);
	}
}

void Archive::close()
{
	m_hH2O.close();
}


//
// Private
//
void Archive::init()
{
	memset(&m_Comment, 0, sizeof(m_Comment));
	memset(&m_Header, 0, sizeof(m_Header));
	memset(&m_Header, 0, sizeof(m_FileNameDesc));
	memset(&m_Header, 0, sizeof(m_DirectoryNameDesc));
	m_pCompressedDirectoryNameChunk = NULL;
	m_pCompressedFileNameChunk = NULL;
	m_arrDirectoryParents = NULL;
}