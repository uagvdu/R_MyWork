#include<iostream>
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

#define N 2

extern "C"
{
	void perror(const char* s);
	char* basename(char* path);
}

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

class LogAnalyze
{
public:
	 
	// 1. 先判断日志类型
	char JudgeFileType(const string &pathname);

	// 2. 按行读取文件内容
	string GetNumLogCon(int fd,char ft,int NUM=1);

	// 2.1 确定第几行的文件内容
	// string GetLogCon(char ft);

	void Display(char ft);

protected:

	//分割字段 函数: 
	void SegField(int fd ,char ft,int NUM=1);	
	//读取文件内容
	int ReadLine(string &buf,int fd ,int NUM=1);
	//将文件内容进行保存
	void SaveField(vector<string>& v,string& buf);

protected:

	Info_AFile Afile;
	Info_BFile Bfile;
};
