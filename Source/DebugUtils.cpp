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
	void debugLog(char* szDesc, char* szString, char* szComment)
	{
		#ifdef _DEBUG
		szDesc = (szDesc==NULL) ? "" : szDesc;
		szString = (szString==NULL) ? "" : szString;
		szComment = (szComment==NULL) ? "" : szComment;
		std::cout << szDesc << szString << szComment << std::endl;
		#endif
	}
	void debugLog(char* szDesc, float szFloat, char* szComment)
	{
		#ifdef _DEBUG
		szDesc = (szDesc==NULL) ? "" : szDesc;
		szComment = (szComment==NULL) ? "" : szComment;
		std::cout << szDesc << std::fixed << std::setprecision(2) << szFloat << szComment << std::endl;
		#endif
	}
	void debugLog(char* szDesc, uint32_t szUint, char* szComment)
	{
		#ifdef _DEBUG
		szDesc = (szDesc==NULL) ? "" : szDesc;
		szComment = (szComment==NULL) ? "" : szComment;
		std::cout << szDesc << szUint << szComment << std::endl;
		#endif
	}
	void debugLog(char* szDesc, uint64_t szUint, char* szComment)
	{
		#ifdef _DEBUG
		szDesc = (szDesc==NULL) ? "" : szDesc;
		szComment = (szComment==NULL) ? "" : szComment;
		#if (_MSC_VER < 1300)	// VC6 doesn't support cout 64bit integer
		std::cout << szDesc;
		printint64(szUint);
		std::cout << szComment << std::endl;
		#else
		std::cout << szDesc << szUint << szComment << std::endl;
		#endif
		#endif
	}
}