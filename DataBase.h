#include "sqlite3.h"
#include "windows.h"

class DataBase
{
public:
    DataBase();
    sqlite3* DB;
    sqlite3_stmt* stmt;
    void writing(const wchar_t* disk, ULONGLONG cluster_number, const wchar_t* sign);
    ~DataBase();
};
