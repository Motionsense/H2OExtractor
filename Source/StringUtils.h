/* StringUtils.h */
#pragma once

#include <string.h>
#include <stdlib.h>
#include "Types.h"

void getFileName(uint32_t index, const char* postfix, char* outputBuffer);
void getFullPath(const char* directoryPath, char* fileName, char* outputBuffer);
