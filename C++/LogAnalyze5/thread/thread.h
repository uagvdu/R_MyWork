#include<iostream>
#include<pthread.h>
#include<string>
#include<unistd.h>

extern pthread_mutex_t mutex; 
extern int a ;
void* ActA(void* arg);
void* ActB(void* arg);
