#include "Fabric.h"

Fabric::Fabric(const WCHAR* path) //Конструктор фабрики (путь лог. тома / файла)
{
    BYTE *pBootRecordBuffer = new BYTE[512];
    Disk = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    ReadFile(Disk, pBootRecordBuffer, 512, 0, NULL);
	Signature = (Sign_Finder*)pBootRecordBuffer;
}

FS Fabric::FS_Definder() //Определение ФС
{
    if (memcmp(Signature->FAT32_Sign, FAT32_Signature, 5) == 0)
    {
        return FS::FAT32;
    }
    else if (memcmp(Signature->NTFS_Sign, NTFS_Signature, 4) == 0)
    {
        return FS::NTFS;
    }
    else return FS::UNKNOWN;
}

BaseFileSystem* Fabric::getFS(FS FS_Defined) //Возврат экземпляра ФС нужного типа
{
    if (FS_Defined == FS::FAT32)
    {
        return new FAT32(Disk);
    }
    else if (FS_Defined == FS::NTFS)
    {
        return new NTFS(Disk);
    }

    else return NULL;
}
