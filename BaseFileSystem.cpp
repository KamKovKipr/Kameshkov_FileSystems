#include "BaseFileSystem.h"

BaseFileSystem::BaseFileSystem(HANDLE Disk) {
	clusterSize = NULL;
	fileHandle = Disk;
}

BaseFileSystem::~BaseFileSystem() {
	CloseHandle(fileHandle);
}

//Чтение данных с заданного смещения
void BaseFileSystem::readBytesFromOffset(LARGE_INTEGER startOffset, BYTE *pResultBuffer, DWORD bytesToRead) {
	unsigned long filePointer = SetFilePointer(fileHandle, startOffset.LowPart, &startOffset.HighPart, FILE_BEGIN);
	if (filePointer == INVALID_SET_FILE_POINTER) {
		throw "Ошибка установки filePointer";
	}

	DWORD bytesRead;
	bool readResult = ReadFile(fileHandle, pResultBuffer, bytesToRead, &bytesRead, NULL);
	if (!readResult || bytesRead != bytesToRead) {
		throw "Ошибка чтения readResult";
	}
}
//Установка размера класстера ФС
void BaseFileSystem::setClusterSize(unsigned int clSize) {
	clusterSize = clSize;
}
//Возвращение значения размера класстера ФС
unsigned int BaseFileSystem::getClusterSize() {
	return clusterSize;
}
//Установка значения количества кластеров ФС
void BaseFileSystem::setNumOfClusters(unsigned int numOfCl) {
	numOfClusters = numOfCl;
}
//Возвращение значения количества кластеров ФС
unsigned int BaseFileSystem::getNumOfClusters() {
	return numOfClusters;
}

