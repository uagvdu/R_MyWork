#include<iostream>
#include"mysql.h"
#include<dlfcn.h>
#include"my_global.h"
#include<string>
using namespace std;




int main()
{
	string str("baike");
	cout<<"Mysql client version: "<<mysql_get_client_info()<<endl;
	MYSQL *conn =mysql_init(NULL);
	if(!conn)
	{
		cout<<"Init failed!"<<endl;
		exit(1);
	}
	
	if(mysql_real_connect(conn,"localhost","adobe","2582","Concurrency",0,NULL,0)==NULL)
	{
		cout<<"connect failed!"<<endl;
		exit(2);
		
	}
	if(mysql_query(conn,"INSERT INTO learn(name,ages)VALUES('"+str+"',69)")!=0) // 成功返回值为0
	{
		cout<<"mysql_query failed !"<<endl;
		exit(3);
		
	}
	if(mysql_store_result(conn))
	{
		cout<<"mysql_store_result failed!"<<endl;
		exit(4);
	}


	return 0;
}
