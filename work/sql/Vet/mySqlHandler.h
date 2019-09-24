#ifndef MY_SQL_HANDLER
#define MY_SQL_HANDLER

#include <mysql/mysql.h>

MYSQL * MySql_Init(MYSQL* _mysql); 
void MySql_Disconnect(MYSQL* _mysql); 
MYSQL * MySql_connect(MYSQL * _mysql, char const* _name, char const* _pass, char const* _db);

MYSQL_RES* MySql_GetAll(MYSQL* _mysql,MYSQL_RES*_myRes, char const* _table, char const* _cond);
void MySql_Insert(MYSQL* _mysql, char const* _table, char const* _columns, char const* _values);
void MySql_Delete(MYSQL* _mysql, char const* _table, char const* _cond);
void MySql_Update(MYSQL* _mysql, char const* _table, char const* _columns, char const* _cond);

void MySqlPrintRes(MYSQL_RES* _res);

void MySqlClose(MYSQL* _mysql, MYSQL_RES* _res);

#endif