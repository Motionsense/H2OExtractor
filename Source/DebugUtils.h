/* DebugUtils.h */
#pragma once

#include <iostream>
#include <iomanip>
#include "Types.h"

namespace DB {
	void printint64(uint64_t i);
	void debugLog(char* szDesc, char* szString, char* szComment, bool isHex=false);
	void debugLog(char* szDesc, float szFloat, char* szComment);
	void debugLog(char* szDesc, int32_t Int32, char* szComment);
	void debugLog(char* szDesc, uint32_t Uint32, char* szComment);
	void debugLog(char* szDesc, uint64_t Uint64, char* szComment);
}



