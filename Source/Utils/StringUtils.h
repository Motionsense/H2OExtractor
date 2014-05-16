/* StringUtils.h */
#pragma once

#include <string.h>
#include <stdlib.h>
#include "../Types.h"

void wtoc(wchar_t *toConvert, char *str);
void ctow(char *toConvert, wchar_t *wstr);
void getFileName(uint32_t index, char* postfix, char* outputBuffer);
void getFullPath(const char* directoryPath, char* fileName, char* outputBuffer);
