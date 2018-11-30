#include <stdio.h>
#include "sqlite.h"

int main(void)
{
	SqliteMemory memdb;
	SqliteAuto backup("backup.db");

	if(backup.Open("backup.db") == false)
	{
		goto error;
	}
	memdb.Begin();
	memdb.Exec("drop table tt");
	memdb.Exec("create table tt(id integer primary key autoincrement, name text)");
	for(int i = 0; i < 100; i++)
	{
		memdb.Exec(xstring("insert into tt(name) values('%x%x')", i, i));
	}
	memdb.Commit();
	memdb.Exec("select * from tt");
	memdb.GetResult().show();
	backup = memdb;
	return 0;
error:
	printf("%s\n", memdb.GetErrorMessage());
	printf("%s\n", backup.GetErrorMessage());
	return -1;
}
