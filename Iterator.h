#include "BaseFileSystem.h"
#include "windows.h"

class Iterator
{
public:
    Iterator(BaseFileSystem* FS);
    BaseFileSystem* MyFS;
    BYTE* pResultBuffer;
    ULONGLONG LastCl;
    ULONGLONG CurCl;
    void First();
    void Next();
    bool IsDone();
    void getCurrentCl();
    Iterator() = default;
};
