#include"thread.h"
#include<string>

//全局内存，堆内存，栈，文件描述符，程序代码： 线程共享

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

int a = 0;
int main()
{
//	std::cout<<"hello "<<std::endl;
//	pthread_t tid1;
//	pthread_t tid2;
//	
//	int err1 = pthread_create(&tid1,NULL,ActA,NULL);	
//	if(err1!=0)
//		std::cout<<"can't create tid1!"<<std::endl;;
//	pthread_join(tid1,NULL);
//
//	int err2 = pthread_create(&tid2,NULL,ActB,NULL);
//	if(err2!=0)
//		std::cout<<"can't create tid2!"<<std::endl;
//	pthread_join(tid2,NULL);
//
//	std::string str("hello world!");
//	int index = str.find(" ");
//	std::cout<<"index: "<<index<<std::endl;
//	int len = str.length()-index;
//	std::cout<<"len: "<<str.length()<<" "<<len<<std::endl;
	
	int i =0;
	while(1)
	{
	i++;
std::cout<<"i"<<std::endl;
 	}


	return  0;
}
//除了共享资源需要加锁外，每一个线程的执行顺序是不确定的
//比如上面的tid1和tid2： 因为顺序的不确定，造成了tid1中的a的值不一定为期望值
//其二： 之所以为其加锁，是为了避免数据的多处写入，
//线程的执行顺序，和资源的加锁是两个不同的概念
