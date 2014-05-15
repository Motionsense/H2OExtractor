/* DebugUtils.cpp */
#include "DebugUtils.h"

namespace DB {
	void printint64(uint64_t i)
	{
		if (i<=100000000)
			printf("%d", i);
		else
		{
			printf("%d", i/100000000);
			printf("%08d", i%100000000);
		}
		fflush(stdout);
	}
	void debugLog(char* szDesc, char* szString, char* szComment, bool isHex)
	{
		szDesc = (szDesc==NULL) ? "" : szDesc;
		szString = (szString==NULL) ? "" : szString;
		szComment = (szComment==NULL) ? "" : szComment;
		if (isHex)
		{
			// Display in big endian order
			std::cout << szDesc << std::hex << std::setfill ('0') << std::setw(8) << *(uint32_t*)szString << std::dec << szComment << std::endl;
		}
		else
			std::cout << szDesc << szString << szComment << std::endl;
	}
	void debugLog(char* szDesc, float szFloat, char* szComment)
	{
		szDesc = (szDesc==NULL) ? "" : szDesc;
		szComment = (szComment==NULL) ? "" : szComment;
		std::cout << szDesc << std::fixed << std::setprecision(2) << szFloat << szComment << std::endl;
	}
	void debugLog(char* szDesc, int32_t Int32, char* szComment)
	{
		szDesc = (szDesc==NULL) ? "" : szDesc;
		szComment = (szComment==NULL) ? "" : szComment;
		std::cout << szDesc << Int32 << szComment << std::endl;
	}
	void debugLog(char* szDesc, uint32_t Uint32, char* szComment)
	{
		szDesc = (szDesc==NULL) ? "" : szDesc;
		szComment = (szComment==NULL) ? "" : szComment;
		std::cout << szDesc << Uint32 << szComment << std::endl;
	}
	void debugLog(char* szDesc, uint64_t Uint64, char* szComment)
	{
		szDesc = (szDesc==NULL) ? "" : szDesc;
		szComment = (szComment==NULL) ? "" : szComment;
		#if (_MSC_VER < 1300)	// VC6 doesn't support cout 64bit integer
		std::cout << szDesc;
		printint64(Uint64);
		std::cout << szComment << std::endl;
		#else
		std::cout << szDesc << Uint64 << szComment << std::endl;
		#endif
	}
}