#include"thread.h"
#include<sys/types.h>
#include<string>
using namespace std;

//全局内存，堆内存，栈，文件描述符，程序代码： 线程共享

struct Dir_ptr
{
	int  a ;	
};


pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

//void * GetFile(void* args)
//{
//	Dir_ptr * dp  = (Dir_ptr*) args;
//	dp->a = 10;
//	//cout << "D : "<<a<<endl;
//}
int a = 1;
//int main()
//{
//	Dir_ptr dp ;
//	dp.a = 0;
//
//	pthread_t tid;
//	pthread_create(&tid,NULL,GetFile,(void*)&dp);
//	//GetFile(&dp);
//	cout<<"a :" <<dp.a<<endl;
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
	
//	int i =0;
//	while(1)
//	{
//	i++;
//std::cout<<"i"<<std::endl;
// 	}
//
//	
//
//	return  0;
//}
//除了共享资源需要加锁外，每一个线程的执行顺序是不确定的
//比如上面的tid1和tid2： 因为顺序的不确定，造成了tid1中的a的值不一定为期望值
//其二： 之所以为其加锁，是为了避免数据的多处写入，
//线程的执行顺序，和资源的加锁是两个不同的概念
//
//
/*
struct A
{
	int a;
	int b ;

};
void* thread_run(void *args)
{
	struct A fp = {3,5};
	pthread_exit((void*)& fp);
}


//父线程传递过去的只是一个值，以后怎么变化，跟父线程已经没有任何关系： 所以说线程栈私有
//即使是主线程也不为过
//
//当某个线程可以修改这个变量而其它线程也可以读取或修改这个变量的时候，就需要对线程进行同步
//当一个线程修改这个变量的时候，其它线程读取这个变量就可能会出现不一致的情况

void* thr(void* args){}

int main()
{	
	pthread_t tid;
	pthread_t tid2;
	struct A* fp;
	//pthread_create(&tid,NULL,thread_run,(void*)&fp);
	pthread_create(&tid,NULL,thread_run,NULL);
	pthread_join(tid,(void**)& fp);

//	pthread_create(&tid2,NULL,thr,NULL);

	cout<<fp->a<<" "<< fp->b<<endl;
	return 0;
	

}
*/
//
//struct A
//{
//	int a ;
//};
//
//int status= 0;
//
//void* thread_run1(void* args)
//{
//	A* ts = (A*) args;
//	ts->a = 20;
//	cout<<"thread 1: "<<ts->a<<endl;
//	pthread_mutex_lock(&mutex);
//	while(status==0)
//	{
//		cout<<"status: "<<status<<endl;
//		pthread_cond_wait(&cond,&mutex);
//	}
//	status = -1;
//	cout<<"cond "<<status<<endl;	
//	pthread_mutex_unlock(&mutex);
//
//}
//
//void* thread_run2(void* args)
//{
//
//	A* ts = (A*) args;
//	ts->a = 10;
//	cout<<"thread 2: "<<ts->a<<endl;
//	pthread_mutex_lock(&mutex);
//	status  = 2;
//	pthread_mutex_unlock(&mutex);
//	
//	cout<<"thread: "<<status<<endl;
//	pthread_cond_signal(&cond);
//
//}
//
//// 1. 互斥量对条件进行保护
//// 2. pthread_cond_wait把线程放到等待条件的线程列表上，然后对互斥量解锁： 解锁后，需要该锁的线程就去获得锁，而该线程等待某一条件的发生，若条件发生，则当wait函数返回时，则互斥量再次被锁住
//// 3. 因为解锁了，所以可以执行tid2，当数据发生更改，条件被唤醒，随时执行tid1
//
//
//
//int main()
//{
//	
//	struct A* ts = new  A;
//	ts->a = 10;
//
//	pthread_t tid1;
//
//	pthread_create(&tid1,NULL,thread_run1,(void*) ts);
//	sleep(1);
//
//	pthread_t tid2;
//	pthread_create(&tid2,NULL,thread_run2,(void*) ts);
//
//	cout<<"main: "<<ts->a<<endl;
//	sleep(1);
//	return 0;
//}
//
//



class Base
{
public:
	Base()
	:count(new int(0))
	{}
	void disp()
	{
		cout <<"Base:  "<<*count<<endl;
	}
	~Base()
	{
		cout<<"Base:"<<endl;
	}
	protected:
		int*	count ;
};
class Div
{
public:
	Div()
	:count(new int(1))
	{}
	void disp()
	{
		cout <<"div: "<< *count<<endl;
	}
	~Div()
	{
		cout<<"Div:"<<endl;
	}
	protected:
		int*	count ;
};


void test(void*a )
{
	Base* b = (Base*)a;	
	
	b->disp();
}
int main()
{
	Div* d = new Div;
	d->disp();
	test(d);

	sleep(1);
	return 0;
}
