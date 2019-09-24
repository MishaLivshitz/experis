#include <stdio.h>
#include <mysql/mysql.h>
int main ()
{
	MYSQL * MySql = NULL;
	MYSQL * ResSql = NULL;

	MYSQL_RES* queryRes = NULL;
	MYSQL_FIELD* fields = NULL;
	MYSQL_ROW rows = NULL;

	int Retvali;
	int rowNum;
	int colNum;

	puts("Starting program");
	MySql = mysql_init(NULL); // MYSQL * MySql ;
	if (MySql == NULL) {
      	fprintf(stderr, "error connecting to mysql errno: %d Msg: %s\n", 
			mysql_errno(MySql), mysql_error(MySql));
     	exit(1);
  	} else {
		puts("mysql_init Succeeded");
	}

	ResSql = mysql_real_connect(MySql, "localhost", "michael", "misha1991", "new_schema", 0, NULL, 0); // MYSQL * ResSql ;
	if (ResSql == NULL) 
	{
      	fprintf(stderr, "error connecting to mysql errno: %d Msg: %s\n", 
			mysql_errno(ResSql), mysql_error(ResSql));
		mysql_close(MySql);
     	exit(1);
  	}   
	else 
	{
		puts("mysql_real_connect Succeeded");
	}

	Retvali = mysql_query(ResSql, "SELECT * from students");


	if(Retvali != 0)
	{
		fprintf(stderr, "error connecting to mysql errno: %d Msg: %s\n", 
			mysql_errno(ResSql), mysql_error(ResSql));
		mysql_close(MySql);
     	exit(1);
	}

	queryRes = mysql_store_result(ResSql);
	if(queryRes == NULL && (mysql_errno(ResSql)!=0))
	{
		fprintf(stderr, "error connecting to mysql errno: %d Msg: %s\n", 
			mysql_errno(ResSql), mysql_error(ResSql));
		mysql_close(MySql);
     	exit(1);
	}

	if(NULL == queryRes)
	{
		puts("Result is NULL");
	}
	else
	{
		int i;
		int j;
		colNum = mysql_num_fields(queryRes);
		rowNum = mysql_num_rows(queryRes);

		for(i = 0 ; i< colNum;++i)
		{
			fields = mysql_fetch_field(queryRes);
			printf("%s: ", fields->name);
		}

		puts("\n");

		for(i = 0 ; i< rowNum;++i)
		{
			rows = mysql_fetch_row(queryRes);
			for(j = 0 ; j< colNum; ++j)
			printf("%s ", rows[j]);
		}

		puts("\n");
	}
	


	mysql_free_result(queryRes);
  	mysql_close(MySql);
	puts("Press enter to terminate");
	getchar();

	return(0);
}
