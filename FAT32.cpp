#include <iostream>
#include "FAT32.h"
#include "windows.h"

FAT32::FAT32(HANDLE Disk) : BaseFileSystem(Disk) {
	LARGE_INTEGER startOffset;
	startOffset.QuadPart = 0;
    #pragma pack(push,1)
	struct FAT32_Struct  //Структура для поиска нужных значений в ФС FAT32
	{
		BYTE jump[11]; // Незначащие байты
		uint16_t bytesPerSector; //Байт в секторе
		uint8_t sectorsPerCluster; //Секторов в кластере
		uint16_t initialSector; //Начальный сектор
		uint8_t countOfFAT; //Количество таблиц FAT
		BYTE jump2[15]; // Незначащие байты
		uint32_t numOfSectors; //Количество секторов
		uint32_t sizeOfFAT; //Размер таблицы FAT
  	};
    #pragma pack(pop)

	BYTE *pBootRecordBuffer = new BYTE[512];
	readBytesFromOffset(startOffset, pBootRecordBuffer, 512);

	//Вычисление требуемых значений (размер кластера и количество кластеров)
	FAT32_Struct* info = (FAT32_Struct*)pBootRecordBuffer;
	int clusterSize = info->bytesPerSector * info->sectorsPerCluster;
	int numOfClusters = info->numOfSectors / info->sectorsPerCluster - (info->initialSector + info->countOfFAT * info->sizeOfFAT) * info->bytesPerSector / clusterSize;
	setClusterSize(clusterSize);
	setNumOfClusters(numOfClusters);


	secondClusterOffset = (info->initialSector + info->countOfFAT * info->sizeOfFAT) * info->bytesPerSector; //Смещение второго кластера

	delete[] pBootRecordBuffer;
}

FAT32::~FAT32() {}

//Чтение определенного кластера
void FAT32::readClusterNumber(unsigned int clusterNumber, BYTE *pResultBuffer)
{
	DWORD clusterSize = getClusterSize();
	if (clusterSize == NULL) {
		throw "Размер кластера не определен";
	}


	LARGE_INTEGER startOffset;
	startOffset.QuadPart = secondClusterOffset + (clusterNumber-2) * clusterSize;

	readBytesFromOffset(startOffset, pResultBuffer, clusterSize);
}
