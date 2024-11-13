#include "DataBase.h"

DataBase::DataBase() //Конструктор БД
{
	const char* filepath = "foundclustersDB.sqlite3"; //Файл создаваемой БД
	sqlite3_open(filepath, &DB); //Открытие БД
	const char* sql = "CREATE TABLE IF NOT EXISTS clusters (number INTEGER, sign TEXT, disk TEXT)";
	sqlite3_exec(DB, sql, NULL, NULL, NULL); //Создание таблицы, если не существует
	sqlite3_prepare(DB, "INSERT INTO clusters VALUES (?, ?, ?)", -1, &stmt, NULL); //Подготовка запроса на запись данных
};

void DataBase::writing(const wchar_t* disk, ULONGLONG cluster_number, const wchar_t* sign)
{
	sqlite3_bind_int64(stmt, 1, cluster_number); //Запись номера класстера
	sqlite3_bind_text16(stmt, 2, sign, -1, SQLITE_TRANSIENT); //Запись расширения
	sqlite3_bind_text16(stmt, 3, disk, -1, SQLITE_TRANSIENT); //Запись данных об объекте анализа
	sqlite3_step(stmt);
    //Подготовка запроса к следующей записи
	sqlite3_reset(stmt);
	sqlite3_clear_bindings(stmt);

};

DataBase::~DataBase()
{
  sqlite3_finalize(stmt);
  sqlite3_close(DB);
};


