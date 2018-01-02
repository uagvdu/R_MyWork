
#include"LogAnalyze.h"


//日志分析： 主线程循环目录，查找是否有新文件
//			其余线程获取文件名去执行日志分析


pair<string,bool> vp[ARR_SIZE];
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cmutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t sql_mutex=PTHREAD_MUTEX_INITIALIZER;
int sql_count = 0;

int status  = 10; //剩余的任务数量

int main()
{
	while(1)
	{
	 	if(InitVp())
		{
			break;
		}

	}
	int count = 0;
	while(1)
	{
		if(run1(NULL))
		{
			count  = 0;
		}
		if(count == 10) //线程的个数和文件个数一致的时候和job为0的时候，不再创建线程
		{
			continue;
		}

		pthread_t tid2;
		pthread_create(&tid2,NULL,thread_run2,NULL); //子线程去循环读取目录中文件名
		count++;
				
	}	
	return 0;
}
