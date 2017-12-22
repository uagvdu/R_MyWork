#include"thread.h"

void* ActA(void* arg)
{
	pthread_mutex_lock(&mutex);
	int count = 10000;
	std::cout<<"thread was begin!"<<std::endl;
	while(count--)
	{
		a++;
		std::cout<<a<<std::endl;
	}
	std::cout<<"thread was done!"<<std::endl;
	pthread_mutex_unlock(&mutex);
}

void* ActB(void* arg)
{
	int count = 10000;
	pthread_mutex_lock(&mutex);
	std::cout<<"thread was begin!"<<std::endl;
	while(count--)
	{
		a--;
		std::cout<<a<<std::endl;
	}
	std::cout<<"thread was done!"<<std::endl;
	pthread_mutex_unlock(&mutex);
}

