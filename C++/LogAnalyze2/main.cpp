#include"LogAnalyze.h"

pthread_mutex_t mutex_dir=PTHREAD_MUTEX_INITIALIZER;



int main()
{
	while(1)
	{
		pthread_mutex_lock(&mutex_dir);
		DIR * dir = NULL;
		dir = opendir("./data");
		struct dirent* ptr=NULL;
		while(ptr=readdir(dir))
		{
			//********设想日志文件有成百上千的类型：即使一个目录只有一种类型，但是有多个目录，总不能每个目录重新写代码吧，
			//************高类聚，低耦合 ; 最大程度的复用****************
			
			string filename(ptr->d_name);
			string pathname="./data/";		
			pathname+=filename;

			//每读取一个文件，就去创建一个线程结构体给日志对象使用，
			thread_stu  ts(pathname);

			//得到文件类型：
			char c = GetFileType(filename);
			switch(c)
			{
				case 'A':
				{
					LogSubA log(ts);
					SubThread(&log);//创建线程					
					remove(pathname.c_str());
					break;
				}
				case 'B':
				{
					LogSubB log(ts);
					SubThread(&log);					
					remove(pathname.c_str());
					break;
				}
				default: //  -1 or others
				//	cout<<"fault: "<<endl;
				break;
			}	
			
			
		}
		pthread_mutex_unlock(&mutex_dir);
		sleep(1);
	}
	return 0;
}

