#include </usr/include/mysql/mysql.h>
#include <string.h>
#include <stdio.h>


#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "gmlwns12"
#define DB_NAME "petmoniter"
#define CHOP(x) x[strlen(x) - 1] = ' '
    
int main(void)
{
    MYSQL       *connection=NULL, conn;
    MYSQL_RES   *sql_result;
    MYSQL_ROW   sql_row;
    int       query_stat; 

    char name[25];
    char address[80];
    char tel[25];
    char query[255];
    
    mysql_init(&conn);

    connection = mysql_real_connect(&conn, DB_HOST,
                                    DB_USER, DB_PASS,
                                    DB_NAME, 0,
                                    (char *)NULL, 0);

    if (connection == NULL)
    {
        fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
        return 1;
    }

    query_stat = mysql_query(connection, "select * from address");
    if (query_stat != 0)
    {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }
    
    sql_result = mysql_store_result(connection);
    
    printf("%+11s %-30s %-10s", "name", "address", "tel");
    while ( (sql_row = mysql_fetch_row(sql_result)) != NULL )
    {
        printf("%+11s %-30s %-10s", sql_row[0], sql_row[1], sql_row[2]);
    }

    mysql_free_result(sql_result);

    printf("name :");
    fgets(name, 25, stdin);
    CHOP(name);

    printf("address :");
    fgets(address, 80, stdin);
    CHOP(address);

    printf("tel :");
    fgets(tel, 25, stdin);
    CHOP(tel);

    sprintf(query, "insert into address values "
                   "('%s', '%s', '%s')",
                   name, address, tel);

    query_stat = mysql_query(connection, query);
    if (query_stat != 0)
    {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }

    mysql_close(connection);
    return 0;
}
