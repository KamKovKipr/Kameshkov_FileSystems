#include "NTFS.h"
#include <iostream>
#include "windows.h"

NTFS::NTFS(HANDLE Disk) : BaseFileSystem(Disk) {
	LARGE_INTEGER startOffset;
	startOffset.QuadPart = 0;
    #pragma pack(push,1)
	struct NTFSS_truct //Структура для поиска нужных значений в ФС NTFS
	{
		BYTE jump[11]; // Незначащие байты
		uint16_t bytesPerSector; //Байт в секторе
		uint8_t sectorsPerCluster; //Секторов в кластере
		BYTE jump2[26]; // Незначащие байты
		uint64_t numOfSectors; //Количество секторов
  	};
	#pragma pack(pop)

	BYTE* pBootRecordBuffer = new BYTE[512];
	readBytesFromOffset(startOffset, pBootRecordBuffer, 512);

	//Вычисление требуемых значений (размер кластера и количество кластеров)
	NTFSS_truct* info = (NTFSS_truct*)pBootRecordBuffer;
    int clusterSize = info->bytesPerSector * info->sectorsPerCluster;
	int numOfClusters = info->numOfSectors / info->sectorsPerCluster;
	setClusterSize(clusterSize);
    setNumOfClusters(numOfClusters);

	delete[] pBootRecordBuffer;
}

NTFS::~NTFS() {}

//Чтение определенного кластера
void NTFS::readClusterNumber(unsigned int clusterNumber, BYTE* pResultBuffer) {
	DWORD clusterSize = getClusterSize();
	if (clusterSize == NULL) {
		throw "Размер кластера не определен";
	}


	LARGE_INTEGER startOffset;
	startOffset.QuadPart = clusterNumber * clusterSize;

	readBytesFromOffset(startOffset, pResultBuffer, clusterSize);
}
