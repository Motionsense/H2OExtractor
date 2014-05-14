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
}

uint64_t Archive::readComment(uint64_t streamPos)
{
	m_hH2O.seekg(streamPos, std::ios::beg);

	// Read Header
	m_hH2O.read(m_Comment.szHeader, 8);
	DB::debugLog("- ArchiveHeader: ", m_Comment.szHeader, NULL);

	// Read VersionInfo
	m_hH2O.read((char*)&m_Comment.VersionInfo, 4);	
	DB::debugLog("- VersionInfo: ", m_Comment.VersionInfo, NULL);

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
	DB::debugLog("- Comments: ", m_Comment.szComments, NULL);
	return end;
}

uint64_t Archive::readHeader(uint64_t streamPos)
{
	m_hH2O.seekg(streamPos, std::ios::beg);
	m_hH2O.read((char*)&m_Header, sizeof(ArchiveHeader));
	DB::debugLog("size: ", sizeof(m_Header.CompressedSize), NULL);
	DB::debugLog("- Version: ", m_Header.Version, NULL);
	DB::debugLog("- FileCount: ", m_Header.FileCount, NULL);
	DB::debugLog("- CompressedSize: ", m_Header.CompressedSize, NULL);
	DB::debugLog("- RawSize: ", m_Header.RawSize, NULL);
	return 0;
}

void Archive::open(char* szFilePath)
{
	m_hH2O.open("Cursors.H2O", std::ifstream::binary);

	uint64_t curPos = 0;
	DB::debugLog("Comment Section: ", "", NULL);
	curPos = readComment(curPos);
	DB::debugLog("Header Section: ", "", NULL);
	curPos = readHeader(curPos);
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
}