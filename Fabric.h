#include "FAT32.h"
#include "NTFS.h"

enum class FS {FAT32, NTFS, UNKNOWN};

    #pragma pack(push,1)
	struct Sign_Finder //Структура для поиска сигнатуры ФС
	{
		BYTE jump[3];
        BYTE NTFS_Sign[4];
        BYTE jump2[75];
        BYTE FAT32_Sign[5];
  	};
    #pragma pack(pop)

 class Fabric
 {
 public:
    FS FS_Definder();
    HANDLE Disk;
    BaseFileSystem* getFS(FS FS_Defined);
    Fabric(const WCHAR* path);
    Sign_Finder* Signature;
    const BYTE NTFS_Signature[4] = { 0x4E, 0x54, 0x46, 0x53 };
	const BYTE FAT32_Signature[5] = { 0x46, 0x41, 0x54, 0x33, 0x32 };
 };
