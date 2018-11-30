#include <stdio.h>
#include "sqlite.h"

Sqlite::Sqlite(void)
{
	db = NULL;
}
Sqlite::~Sqlite(void)
{
}
bool Sqlite::Copy(const Sqlite& s)
{
	if(GetErrorCode() != SQLITE_OK)
	{
		return false;
	}
	if(s.GetErrorCode() != SQLITE_OK)
	{
		return false;
	}
	sqlite3_backup *b = NULL;
	if(b = sqlite3_backup_init(db, "main", s.db, "main"))
	{
		if(sqlite3_backup_step(b, -1) != SQLITE_DONE)
		{
			sqlite3_backup_finish(b);
			return false;
		}
		return sqlite3_backup_finish(b) == SQLITE_OK;
	}
	return false;
}
bool Sqlite::Open(const xstring& fname)
{
	Close();
	if( sqlite3_open(fname.data(), &db) == SQLITE_OK)
	{
		return true;
	}
	return false;
}
bool Sqlite::Exec(const xstring& sql)
{
	result.clear();
	return sqlite3_exec(db, sql.data(), Qurey, this, NULL) == SQLITE_OK;
}
bool Sqlite::Backup(const xstring& fname)
{
	SqliteAuto dest;
	sqlite3_backup *backup = NULL;
	
	if(dest.Open(fname) == false)
	{
		return false;
	}
	backup = sqlite3_backup_init(dest.db, "main", db, "main"); 
	if(backup)
	{
		if(sqlite3_backup_step(backup, -1) == SQLITE_DONE)
		{
			return sqlite3_backup_finish(backup) == SQLITE_OK;
		}
		sqlite3_backup_finish(backup);	
	}
	return false;
}
bool Sqlite::Begin(void)
{
	return sqlite3_exec(db, "begin", 0, 0, 0) == SQLITE_OK;
}
bool Sqlite::Commit(void)
{
	return sqlite3_exec(db, "commit", 0, 0, 0) == SQLITE_OK;
}
void Sqlite::Close(void)
{
	if(NULL != db)
	{
		Commit();
		sqlite3_close(db);
		db = NULL;
	}
}
const int Sqlite::Changes(void)
{
	return sqlite3_changes(db);
}
const char* Sqlite::GetName(void)
{
	return sqlite3_db_filename(db, NULL);
}
const char* Sqlite::GetErrorMessage(void)
{
	return sqlite3_errmsg(db);
}
const Result& Sqlite::GetResult(void)
{
	return result;
}
const int Sqlite::GetErrorCode(void)const
{
	return sqlite3_errcode(db);
}
Sqlite& Sqlite::operator=(const Sqlite& s)
{
	this->Copy(s);
	return *(Sqlite*)this;
}
int Sqlite::Qurey(void *p, int count, char **values, char **names)
{
	Sqlite &db = *(Sqlite*)p;
	Result &result = db.result; 
	Row &row = result[ result.size() ];

	for(int i = 0; i < count; i++)
	{
		row[i][ (names[i]) ] = values[i];
	}
	return 0;
}
