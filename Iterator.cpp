#include "Iterator.h"

Iterator::Iterator(BaseFileSystem* FS) //Конструктор итератора (экземпляр ФС)
{
    MyFS = FS;
    CurCl = 0;
    LastCl = FS -> getNumOfClusters();
    pResultBuffer = new BYTE[FS -> getClusterSize()];
    int b = 0;
}

void Iterator::First() //Установка текузего кластера в нулевое значение
{
    CurCl = 0;
}

void Iterator::Next() //Переход к следующему кластеру
{
    CurCl++;
}

bool Iterator::IsDone() //Проверка обхода ФС
{
    if (CurCl>=LastCl)
    {
        return true;
    }
    else return false;
}

void Iterator::getCurrentCl() //Чтение текущего кластера
{
    MyFS->readClusterNumber(CurCl, pResultBuffer);
}

