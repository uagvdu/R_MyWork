#include<iostream>
#include<cstring>
#include<cstdlib>
#include<stdlib.h>
#include<cstdio>
#include<string>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
using namespace std;

#define FD_SIZE 100

void FillFile(int fd)
{
	int count = 1;		

	string str="18633356789|2|yd|173.16.21.10|3345|2.56.3.77|8000|2017-11-02 10:02:11|http://blog.csdn.net/pi9nc/article/details/";
	while(count<=1000000)
	{
		char str_buf[1024];
		memset(str_buf,0,1024);
		sprintf(str_buf,"%d\n",count);
		//str+=string(str_buf); //因为这步，所以str需要每次都放在while循环中，
		write(fd,(str+str_buf).c_str(),(str+str_buf).length());
		count++;
	}
	
}

int main()
{
	string dir= "../data/";
	char buf[1024];

	string file="A"	;
	if(access(dir.c_str(),0)==-1)
	{
		mkdir(dir.c_str(),0777);
	}

	while(1)
	{
		int count = 1;
		//创建十个文件： 并分别往十个文件内部写入数据
		while(count < FD_SIZE)
		{	
			memset(buf,0,1024);
			sprintf(buf,"%d",count);
		//	cout<<"buf: "<<buf<<endl;
			string filename=dir+ file+string(buf);
			string newfile=filename+".ok";
			if(access(newfile.c_str(),0) != -1)
			{
				count++;
				continue;
			}
			int fd = open(filename.c_str(),O_RDWR|O_CREAT,0777);
			if(fd<0)
				cout<<"open failed !"<<endl;

			FillFile(fd);
			rename(filename.c_str(),newfile.c_str());
			sleep(1);
				
			count++;
		}

	}	
	return 0;
}
