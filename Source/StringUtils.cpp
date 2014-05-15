/* StringUtils.cpp */
#include "StringUtils.h"

// TODO: Use native char array

void getFileName(uint32_t index, const char* postfix, char* outputBuffer)
{
	memset(outputBuffer, 0, 16);
	char szIndex[8];
	itoa (index, szIndex, 10);
	strcpy(outputBuffer, szIndex);
	strcat(outputBuffer, postfix);
}

void getFullPath(const char* directoryPath, char* fileName, char* outputBuffer)
{
	memset(outputBuffer, 0, 64);
	strcpy(outputBuffer, directoryPath);
	strcat(outputBuffer, fileName);
}