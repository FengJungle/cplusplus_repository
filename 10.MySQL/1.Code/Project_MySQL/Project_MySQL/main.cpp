#define _CRT_SECURE_NO_WARNINGS
#include <winsock.h>
#include <mysql.h>

#pragma comment(lib, "libmysql.lib")

#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
using namespace std;


// mysql����
MYSQL mysql;

/************��������*************/
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
	// ��ѯ���
	char query[128];

	strcpy(query, "select e.ename, e.sal, s.grade from emp e left join salgrade s on e.sal between s.losal and s.hisal");

	// �����ѯ�ɹ�������0��������ִ��󣬷��ط�0ֵ
	if (mysql_query(&mysql, query) != 0)
	{
		printf("Query failed (%s)\n", mysql_error(&mysql));
		 return false;
	}
	printf("Query success!\n");

	// �����е�һ����ѯ�����
	MYSQL_RES* res;

	// ��ȡ��ѯ���
	if (!(res = mysql_store_result(&mysql)))
	{
		printf("Could not get result from %s\n", mysql_error(&mysql));
		return false;
	}

	// ��ȡ��������
	int rows = mysql_affected_rows(&mysql);
	printf("number of dataline returned: %d\n", rows);
	
	//  ��ȡÿ�����ݵ�����
	unsigned int num_of_field = mysql_num_fields(res);

	// �ֶ�������
	MYSQL_FIELD *fd;
	// �洢�ֶ���
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
	// �����ݵ����Ͱ�ȫ�ı�ʾ����ʾ�����е���
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
	// sql���
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
	// sql���
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