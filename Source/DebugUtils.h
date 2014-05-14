/* DebugUtils.hpp */
#pragma once
#include <iostream>
#include <iomanip>
#include "Types.h"

namespace DB {
	void printint64(uint64_t i);
	void debugLog(char* szDesc, char* szString, char* szComment);
	void debugLog(char* szDesc, float szFloat, char* szComment);
	void debugLog(char* szDesc, uint32_t szUint32, char* szComment);
	void debugLog(char* szDesc, uint64_t szUint64, char* szComment);
}



