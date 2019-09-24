#include "mySqlHandler.h"
#include <stdio.h>
#include <string.h>

#define SELECT_ALL  "SELECT * FROM "
#define INSERT_ONE  "INSERT INTO  "
#define DELETE_ONE  "DELETE FROM "


static int MySql_Query(MYSQL* _mySql, char const* _statement)
{
	int Retvali = mysql_query(_mySql, _statement);

	if(Retvali != 0)
	{
		fprintf(stderr, "Bad statement: %d Msg: %s\n", 
			mysql_errno(_mySql), mysql_error(_mySql));
		return 0;
	}

	return 1;
}

static MYSQL_RES* MySql_Store(MYSQL* _mySql, MYSQL_RES* _myRes)
{
	_myRes = mysql_store_result(_mySql);

	if(_myRes == NULL && (mysql_errno(_mySql)!=0))
	{
		fprintf(stderr, "error connecting to mysql errno: %d Msg: %s\n", 
			mysql_errno(_mySql), mysql_error(_mySql));
		mysql_close(_mySql);
     	exit(1);
	}

	return _myRes;
}

MYSQL * MySql_Init(MYSQL* _mysql)
{
    _mysql = mysql_init(NULL); // MYSQL * MySql ;
	if (_mysql == NULL) 
    {
      	fprintf(stderr, "error connecting to mysql errno: %d Msg: %s\n",
		   mysql_errno(_mysql), mysql_error(_mysql));
     	exit(1);
  	}

    return _mysql;
}

MYSQL * MySql_connect(MYSQL * _mysql, char const* _name, char const* _pass, char const* _db)
{
    MYSQL * ResSql;
    ResSql = mysql_real_connect(_mysql, "localhost", _name, _pass, _db, 0, NULL, 0);
	if (ResSql == NULL) 
	{
      	fprintf(stderr, "error connecting to mysql errno: %d Msg: %s\n", 
			mysql_errno(ResSql), mysql_error(ResSql));
		mysql_close(_mysql);
     	exit(1);
  	}   
	
    return ResSql;
}

MYSQL_RES* MySql_GetAll(MYSQL* _mysql, MYSQL_RES* _myRes, char const* _table, char const* _cond)
{
	char statement[256] = SELECT_ALL;
	strcat(statement, _table);

	if(_cond)
	{
		strcat(statement," WHERE ");
		strcat(statement, _cond);
	}

	MySql_Query(_mysql, statement);

	_myRes = MySql_Store(_mysql, _myRes);

	return _myRes;
}

void MySql_Insert(MYSQL* _mysql, char const* _table, char const* _columns, char const* _values)
{
	char statement[512] = INSERT_ONE;
	strcat(statement, _table);
	strcat(statement, "(");
	strcat(statement, _columns);
	strcat(statement, ")");
	strcat(statement, " VALUES (");
	strcat(statement, _values);
	strcat(statement, ")");

	MySql_Query(_mysql, statement);

}

void MySql_Update(MYSQL* _mysql, char const* _table, char const* _columns, char const* _cond)
{
	char statement[512] = "UPDATE ";
	strcat(statement, _table);
	strcat(statement, " SET ");
	strcat(statement, _columns);

	if(_cond)
	{
		strcat(statement, " WHERE ");
		strcat(statement, _cond);
	}

	MySql_Query(_mysql, statement);

}

void MySql_Delete(MYSQL* _mysql, char const* _table, char const* _cond)
{
	char statement[512] = DELETE_ONE;
	strcat(statement, _table);
	strcat(statement, " WHERE ");
	strcat(statement, _cond);

	MySql_Query(_mysql, statement);

}

void MySqlClose(MYSQL* _mysql, MYSQL_RES* _res)
{
	mysql_free_result(_res);
  	mysql_close(_mysql);
}

void MySqlPrintRes(MYSQL_RES* _res)
{
	MYSQL_ROW rows = NULL;

	if(NULL != _res)
	{
		int i;
		int j;
		int colNum = mysql_num_fields(_res);
		int rowNum = mysql_num_rows(_res);

		puts("\n");

		for(i = 0 ; i< rowNum;++i)
		{
			rows = mysql_fetch_row(_res);
			for(j = 0 ; j< colNum; ++j)
			{
				printf("%s ", rows[j]);
			}
			puts("\n");
		}

	}
}
