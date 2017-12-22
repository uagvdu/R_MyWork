#include<iostream>
#include<pthread.h>
#include<fstream>
#include<istream>
#include<ostream>
#include<vector>
#include<stdlib.h>
#include<cstring>
#include<libgen.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string>
#include<dirent.h>
#include<unistd.h>
using namespace std;


extern pthread_mutex_t mutex;
extern pthread_mutex_t mutex_dir;


struct thread_stu
{
	pthread_mutex_t mutex;
	string pathname;
	
	thread_stu(string pname)
	:pathname(pname)
	{
		pthread_mutex_init(&mutex,NULL);
	}
	
};
//A type file
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

//B type file
struct Info_BFile
{
	string _phone;
	string _num;
	string _user;
	string _host;
	//begin-end;
	string _dateb;
	string _datee;
};

class LogBase;
class LogSubA;
class LogSubB;



char GetFileType(const string &filename);
int SubThread(LogBase* log);
void DealFile(const string& pathname);

class LogBase
{
	public:
		virtual	void SegField(string pathname )=0;
		static void* thread_run(void* args);
		virtual	thread_stu GetTs()=0; 
	protected:
		void SaveField(vector<string>& v,string buf);
};


class LogSubA:public LogBase
{
	public:
		LogSubA(thread_stu _ts);
		void SegField(string pathname );
		void Display();
		thread_stu GetTs(); 
	protected:
		Info_AFile Afile;		
		thread_stu ts;
};


class LogSubB:public LogBase
{
	public:
		LogSubB(thread_stu _ts);
		void SegField(string pathname);
		void Display();
		thread_stu GetTs(); 
	protected:	
		Info_BFile Bfile;
		thread_stu ts;
};
