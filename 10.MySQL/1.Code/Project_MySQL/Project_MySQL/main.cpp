#define _CRT_SECURE_NO_WARNINGS
#include <winsock.h>
#include <mysql.h>

#pragma comment(lib, "libmysql.lib")

#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
using namespace std;


// mysql连接
MYSQL mysql;

/************函数声明*************/
bool ConnectDatabase();
void FreeConnect();
bool QueryDatabase();
bool InsertData();
bool ModifyData();
bool DeleteData();
/********************************/


int main(int argc, char* argv[])
{
	ConnectDatabase();

	QueryDatabase();
	//InsertData();
	ModifyData();
	DeleteData();

	FreeConnect();
	return 0;
}

bool ConnectDatabase()
{
	mysql_init(&mysql);
	if (mysql_real_connect(
		&mysql,
		"127.0.0.1",
		"root",
		"feng2019",
		"mydatabase1",
		3306,
		NULL,
		0
	) == NULL)
	{
		printf("mysql_real_connect failed!\n");
		return false;
	}
	unsigned long thread_id = mysql_thread_id(&mysql);
	printf("Connect success! Thread id is: %d\n", thread_id);
	
	const char* client_info = mysql_get_client_info();
	const char* host_info = mysql_get_host_info(&mysql);
	unsigned long proto_info = mysql_get_proto_info(&mysql);
	const char* server_info = mysql_get_server_info(&mysql);
	printf("Client info : %s\n", client_info);
	printf("Host info : %s\n", host_info);
	printf("proto info : %d\n", proto_info);
	printf("Server info : %s\n", server_info);
	
	printf("\n");
	return true;
}

void FreeConnect()
{
	
	mysql_close(&mysql);
}

bool QueryDatabase()
{
	// 查询语句
	char query[128];

	strcpy(query, "select e.ename, e.sal, s.grade from emp e left join salgrade s on e.sal between s.losal and s.hisal");

	// 如果查询成功，返回0。如果出现错误，返回非0值
	if (mysql_query(&mysql, query) != 0)
	{
		printf("Query failed (%s)\n", mysql_error(&mysql));
		 return false;
	}
	printf("Query success!\n");

	// 返回行的一个查询结果集
	MYSQL_RES* res;

	// 获取查询结果
	if (!(res = mysql_store_result(&mysql)))
	{
		printf("Could not get result from %s\n", mysql_error(&mysql));
		return false;
	}

	// 获取数据行数
	int rows = mysql_affected_rows(&mysql);
	printf("number of dataline returned: %d\n", rows);
	
	//  获取每行数据的列数
	unsigned int num_of_field = mysql_num_fields(res);

	// 字段列数组
	MYSQL_FIELD *fd;
	// 存储字段名
	vector<string> colunm_field(num_of_field);
	for (int i = 0; fd = mysql_fetch_field(res); i++)
	{
		colunm_field[i] = string(fd->name);
	}

	for (int i = 0; i < num_of_field; i++)
	{
		printf("%s\t", colunm_field[i].c_str());
	}
	printf("\n");
	// 行数据的类型安全的表示，表示数据行的列
	MYSQL_ROW column;
	while (column = mysql_fetch_row(res))
	{
		for (int i = 0; i < num_of_field; i++)
		{
			printf("%s\t", column[i]);
		}
		printf("\n");
	}
	mysql_free_result(res);
	return true;
}

bool InsertData()
{
	// sql语句
	char query[128];

	strcpy(query, "insert into t_user (id, username) values (5, 'feng')");
	if (mysql_query(&mysql, query))
	{
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	printf("Insert success!\n");
	return true;
}

bool ModifyData()
{
	// sql语句
	char query[128];
	strcpy(query, "update t_user set username='Jungle' where id = 5");
	if (mysql_query(&mysql, query))
	{
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	printf("Update success!\n");
	return true;
}

bool DeleteData()
{
	char query[100];
	strcpy(query, "delete from t_user where id = 5");
	if (mysql_query(&mysql, query))
	{
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	printf("Delete success!\n");
	return true;
}