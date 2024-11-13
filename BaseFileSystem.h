#pragma once
#include <windows.h>
#pragma once

class BaseFileSystem
{
private:
    unsigned int clusterSize;
    unsigned int numOfClusters;
    HANDLE fileHandle;

protected:
    void readBytesFromOffset(LARGE_INTEGER startOffset, BYTE *pResultBuffer, DWORD bytesToRead);
    void setClusterSize(unsigned int clSize);
    void setNumOfClusters(unsigned int numOfCl);

public:
    virtual unsigned int getClusterSize();
    virtual unsigned int getNumOfClusters();
    virtual void readClusterNumber(unsigned int clusterNumber, BYTE* pResultBuffer) = 0;

    BaseFileSystem(HANDLE Disk);
    ~BaseFileSystem();
};
