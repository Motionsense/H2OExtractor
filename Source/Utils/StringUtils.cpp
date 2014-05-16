/* StringUtils.cpp */
#include "StringUtils.h"

void wtoc(wchar_t *toConvert, char *str)
{
	int count = 0;
	int len = wcslen(toConvert);

	for(; count < len; count++)
	{
		str[count] = (char) toConvert[count];
	}
}

void ctow(char *toConvert, wchar_t *wstr)
{
	int count = 0;
	int len = strlen(toConvert);

	for(; count < len; count++)
	{
		wstr[count] = (wchar_t) toConvert[count];
	}
}

void getFileName(uint32_t index, char* postfix, char* outputBuffer)
{
	memset(outputBuffer, 0, 128);
	char szIndex[8];
	itoa(index, szIndex, 10);
	strcpy(outputBuffer, szIndex);
	strcat(outputBuffer, postfix);
}

void getFullPath(const char* directoryPath, char* fileName, char* outputBuffer)
{
	memset(outputBuffer, 0, 256);
	if (strlen(directoryPath)!=0)
		strcpy(outputBuffer, directoryPath);
	strcat(outputBuffer, fileName);
}