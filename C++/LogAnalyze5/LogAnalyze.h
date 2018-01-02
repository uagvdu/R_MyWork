#include"mysql.h"

#include<iostream>
#include<pthread.h>
#include<fstream>
#include<istream>
#include<ostream>
#include<stdlib.h>
#include<cstring>
#include<libgen.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string>
#include<dirent.h>
#include<unistd.h>
#include<vector>
#include<utility>
using namespace std;

#define ARR_SIZE 10


extern pthread_mutex_t mutex;
extern pthread_mutex_t cmutex;
extern pthread_mutex_t sql_mutex;
extern pair<string,bool> vp[];
extern int status;
extern int sql_count;

struct Info_AFile
{
	string _phone;
	string _num;
	string _user;
	string _hostA;
	string _portA;
	string _hostB;
	string _portB;
	string _date;
	string _url;
};

struct Info_BFile
{
	string _phone;
	string _num;
	string _user;
	string _host;
	string _dateb;
	string _datee;
};




class LogBase;
class LogSubA;
class LogSubB;


bool   run1(void* args);
void* thread_run2(void* args);
void GetFileName(string &pathname);
char CheckFileType(const string& pathname);
bool InitVp();


// 一个目录中有多种日志，其中父类处理的是同一的操作，子类只需要处理独属于自己的操作


//总是想着继承父类就一定要用到父类的对象： 但是父类还有另一种功能： 为子类提供统一接口的作用
//用到了继承，不一定非要用到父类的对象，也可以让父类只起一个提供统一接口的作用
//
class LogBase
{
	public:
		virtual	void  SegField(string pathname) = 0;
		void SaveField(vector<string>& v,string buf);
		void InsertSQL();

	protected:

};


class LogSubA:public LogBase
{
	public:
		LogSubA();
		void  SegField(string pathname) ;
		void InsertSQL();
	protected:
		Info_AFile Afile;		
		MYSQL* conn;
};


class LogSubB:public LogBase
{
	public:
		LogSubB();
		void  SegField(string pathname) ;
		void InsertSQL();
	protected:	
		Info_BFile Bfile;
		MYSQL* conn;
};

