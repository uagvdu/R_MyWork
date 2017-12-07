#include"test.h"


int main()
{
		DIR * dir = NULL;
		dir = opendir("./data");
		struct dirent* ptr=NULL;
		while(ptr=readdir(dir))
		{
			
			if(*(ptr->d_name)!='A'&&*(ptr->d_name)!='B')
				continue;
			string filename(ptr->d_name);
			LogAnalyze log;
			
			//1. 判断文件类型
			char ft = log.JudgeFileType(filename); 
			string pathname="./data/";		
			pathname+=filename;
			int fd = open(pathname.c_str(),O_RDONLY);
			if(fd<0)
			{
				cout<<"fd is failed!" <<endl;
				exit(4);
			}

			//2. 从fd中读取文件内容 ： 此时是行
			log.GetNumLogCon(fd,ft,1);		

			close(fd);
			cout<<"\033[34;1m =================== \033[0m"<<endl;
			cout<<endl;
		}
	return 0;
}
