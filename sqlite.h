#ifndef __SQLITEAPI__
#define __SQLITEAPI__
#include <map>
#include <stdio.h>
#include <sqlite3.h>
#include "xstring.h"

class Column
{
	public:
		xstring key;
		xstring value;
	public:
		xstring& operator[](const string& k)
		{
			this->key = k;
			return value;
		}
		const void show(void)const
		{
			printf("[%s]=%-10s\t", key.data(), value.data());
		}
};
class Row
{
	private:
		map<int,Column> colums;
	public:
		typedef map<int,Column>::const_iterator iterator;
		void clear(void)
		{
			colums.clear();
		}
		Column& operator[](int i)
		{
			return colums[i];
		}
	public:
		iterator begin(void) const
		{
			return colums.begin();
		}
		iterator end(void) const
		{
			return colums.end();
		}
		const int size(void)const
		{
			return colums.size();
		}
		const void show(void)const
		{
			for(iterator i = begin(); i != end(); i++)
			{
				i->second.show();
			}
			printf("\n");
		}
};
class Result
{
	private:
		map<int,Row> rows;
	public:
		typedef map<int,Row>::const_iterator iterator;
		void clear(void)
		{
			rows.clear();
		}
		Row& operator[](int i)
		{
			return rows[i];
		}
	public:
		iterator begin(void) const
		{
			return rows.begin();
		}
		iterator end(void) const
		{
			return rows.end();
		}
		const int size(void) const
		{
			return rows.size();
		}
		const void show(void) const
		{
			for(iterator i = begin(); i != end(); i++)
			{
				i->second.show();
			}
			printf("\n");
		}
};

class Sqlite
{
protected:
	sqlite3 *db;
	Result result;
public:
	Sqlite(void);
	~Sqlite(void);
public:
	bool Copy(const Sqlite&);
	bool Open(const xstring&);
	bool Exec(const xstring&);
	bool Backup(const xstring&);
	bool Begin(void);
	bool Commit(void);
	void Close(void);
public:
	const int Changes(void);
	const char* GetName(void);
	const char* GetErrorMessage(void);
	const int GetErrorCode(void)const;
	const Result& GetResult(void);
public:
	Sqlite& operator=(const Sqlite&);

public:
	static int Qurey(void*,int,char**,char**);
};
class SqliteAuto : public Sqlite
{
public:
	SqliteAuto(void){}
	~SqliteAuto(void)
	{
		Close();
	}
	SqliteAuto(const string& fname)
	{
		Open(fname);
	}
	SqliteAuto& operator=(const Sqlite& s)
	{
		this->Copy(s);
		return *this;
	}
};
class SqliteMemory : public Sqlite
{
public:
	SqliteMemory(void)
	{
		Open(":memory:");
	}
	~SqliteMemory(void)
	{
		Close();
	}
	SqliteMemory& operator=(const Sqlite& s)
	{
		this->Copy(s);
		return *this;
	}
};

#endif//__SQLITEAPI__
