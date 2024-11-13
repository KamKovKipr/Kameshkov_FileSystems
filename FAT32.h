#include <windows.h>
#include "BaseFileSystem.h"
#pragma once

class FAT32 : public BaseFileSystem
{
private:
    unsigned int secondClusterOffset;

public:
    void readClusterNumber(unsigned int clusterNumber, BYTE *pResultBuffer);

    FAT32(HANDLE Disk);
    ~FAT32();
};
