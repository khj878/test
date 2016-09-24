#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

void finish_with_error(MYSQL *conn)
{
	fprintf(stderr, "%s\n", mysql_error(conn));
	mysql_close(conn);
	exit(1);
}

int main(int argc, char *argv[])
{
	MYSQL *conn = mysql_init(NULL);

	if(conn == NULL)
	{
		fprintf(stderr, "mysql_init() errorrrrrrrr\n");
		exit(1);
	}
	if(mysql_real_connect(conn, "localhost", "root", "gmlwns12", "petmoniter", 0, NULL, 0) == NULL)
	{
		finish_with_error(conn);
	}

	if(mysql_query(conn, "SELECT * FROM address"))
	{
		finish_with_error(conn);
	}

	MYSQL_RES *result = mysql_store_result(conn);
	if(result == NULL)
	{
		finish_with_error(conn);
	}

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;
	while(row = mysql_fetch_row(result))
	{
		for(int i = 0; i < num_fields; i++)
		{
			printf("%s    ", row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}

	mysql_free_result(result);
	mysql_close(conn);
	exit(0);
}
