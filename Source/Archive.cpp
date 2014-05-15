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
	delete[] m_aDirectoryParents;
	delete[] m_pFileNameChunk;
	delete[] m_pDirectoryNameChunk;
	delete[] m_Comment.szComments;
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

#if _DEBUG
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

#if _DEBUG
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
		m_FileList.push_back(curFile);

	#if _DEBUG
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

	#if _DEBUG
		DB::debugLog("- CompressedSize: ", m_FileNameDesc.CompressedSize, NULL);
		DB::debugLog("- RawSize: ", m_FileNameDesc.RawSize, NULL);
		DB::debugLog("- CRC32[hex]: ", m_FileNameDesc.CRC32, NULL, true);
	#endif
	return m_hH2O.tellg();
}

uint64_t Archive::readFileNameChunk(uint64_t streamPos)
{
	m_hH2O.seekg(streamPos, std::ios::beg);
	m_pFileNameChunk = new char[m_FileNameDesc.CompressedSize];
	m_hH2O.read(m_pFileNameChunk, m_FileNameDesc.CompressedSize);
	// TODO: Decompress the file name chunk
	return m_hH2O.tellg();
}

uint64_t Archive::readDirectoryNameDesc(uint64_t streamPos)
{
	m_hH2O.seekg(streamPos, std::ios::beg);
	m_hH2O.read((char*)&m_DirectoryNameDesc, sizeof(ArchiveDirectoryNameDesc));

	#if _DEBUG
		DB::debugLog("- CompressedSize: ", m_DirectoryNameDesc.CompressedSize, NULL);
		DB::debugLog("- RawSize: ", m_DirectoryNameDesc.RawSize, NULL);
		DB::debugLog("- CRC32[hex]: ", m_DirectoryNameDesc.CRC32, NULL, true);
	#endif
	return m_hH2O.tellg();
}

uint64_t Archive::readDirectoryNameChunk(uint64_t streamPos)
{
	m_hH2O.seekg(streamPos, std::ios::beg);
	m_pDirectoryNameChunk = new char[m_DirectoryNameDesc.CompressedSize];
	m_hH2O.read(m_pDirectoryNameChunk, m_DirectoryNameDesc.CompressedSize);
	// TODO: Decompress the file name chunk
	return m_hH2O.tellg();
}

uint64_t Archive::readDirectoryParents(uint64_t streamPos)
{
	m_hH2O.seekg(streamPos, std::ios::beg);
	m_hH2O.read((char*)&m_DirectoryCount, sizeof(m_DirectoryCount));
	m_aDirectoryParents = new int32_t[m_DirectoryCount];
	m_hH2O.read((char*)m_aDirectoryParents, sizeof(*m_aDirectoryParents)*m_DirectoryCount);

	#if _DEBUG
	DB::debugLog("Directory Count: ", m_DirectoryCount, NULL);
	for (int i=0; i<m_DirectoryCount; i++)
	{
		DB::debugLog("-> ", *(m_aDirectoryParents), "");
	}
	#endif
	return m_hH2O.tellg();
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
	
	DB::debugLog("\nFileNameDesc Section: ", "", NULL);
	curPos = readFileNameDesc(curPos);
	curPos = readFileNameChunk(curPos);

	DB::debugLog("\nDirectoryNameDesc Section: ", "", NULL);
	curPos = readDirectoryNameDesc(curPos);
	curPos = readDirectoryNameChunk(curPos);

	DB::debugLog("\nDirectoryParents Section: ", "", NULL);
	curPos = readDirectoryParents(curPos);
}

void Archive::extractByIndex(uint32_t index)
{
	ArchiveFile& rFile = m_FileList[index];
	char* buffer = new char[rFile.CompressedSize];
	m_hH2O.seekg(rFile.Offest, std::ios::beg);
	m_hH2O.read(buffer, rFile.CompressedSize);

	// generate file name and create directory
	const char* dirPath = "output/";
	if (checkPathType(dirPath)!=TYPE_DIR)
		mkdir(dirPath);
	char fileName[16];
	char fullPath[64];
	getFileName(index, ".wav", fileName);
	getFullPath("output/", fileName, fullPath);
	std::ofstream destFile;

	// write file
	destFile.open(fullPath, std::ofstream::binary);
	destFile.write(buffer, rFile.CompressedSize);
	destFile.close();
	
	delete[] buffer;
}

void Archive::extractAll()
{
	for (int i=0; i<m_Header.FileCount; i++)
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
}