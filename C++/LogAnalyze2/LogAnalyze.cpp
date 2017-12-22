#include"LogAnalyze.h"



//每一个文件有自己独有的锁，因为一个文件就是一个公共资源，那么一个公共资源就只能有一个独有的锁

//	pthread_create(&tid,NULL,log->thread_run,(void*)log);//隐含的this指针，所以会造成参数匹配不当
//
int SubThread(LogBase *log)
{
	pthread_t tid;
	pthread_create(&tid,NULL,LogBase::thread_run,(void*)log);

//	cout<<"\033[34;1m =================== \033[0m"<<endl;
//	cout<<endl;
	pthread_join(tid,NULL);
	return 1;
}
//****************************************************************************************

 void * LogBase::thread_run(void *args)
{
	pthread_detach(pthread_self());
	LogBase *log = (LogBase*)args;
	string pathname = (log->GetTs()).pathname;
	pthread_mutex_t mutex = (log->GetTs()).mutex;
	
	pthread_mutex_lock(&mutex);
//	cout<<"\033[35;1m =================== \033[0m"<<endl;
//	cout<<"pathname" <<pathname<<endl;
//	cout<<"\033[35;1m =================== \033[0m"<<endl;
//	cout<<"lock begin "<<endl;
	log->SegField(pathname);
	pthread_mutex_unlock(&mutex);
//	cout<<"lock end "<<endl;
//	cout<<"\033[34;1m =================== \033[0m"<<endl;
}

//****************************************************************************************


//void LogBase::SegField(string pathname){}

void LogBase::SaveField(vector<string> &v,string buf)
{
	int index1 = buf.find("|");
	int index2 = index1;
	string tmp;	
	v.push_back(string(buf,0,index1));

	while(index1 != std::string::npos && index2 != std::string::npos)
	{	
		index2 = buf.find("|",index1+1);
		if(index2 == std::string::npos)
			break;
	    tmp = buf.substr(index1+1,index2-index1-1);	
		v.push_back(tmp);	
		index1 = index2;
	}

	// 总长度 - 前面不需要的长度 = 目标长度
	tmp = buf.substr(index1+1,buf.length()-1-index1);
	v.push_back(tmp);
		
}


LogSubA::LogSubA(thread_stu _ts)
	:ts(_ts)
{}

thread_stu LogSubA::GetTs()
{
	return ts;	
}

void LogSubA::SegField(string pathname)
{
	ifstream fs ;
	fs.open(pathname.c_str());
	if(!fs)
	{
		cout<<"file open failed!"<<endl;
	}
	while(fs.peek()!=EOF) //EOF = -1
	{
		char cbuf[1024];
		fs.getline(cbuf,1024);	
		string buf=cbuf;

		// 将已经分离的数据放在顺序表中
		vector<string> v;
		SaveField(v,buf);

		this->Afile._phone=v[0];
		this->Afile._num  =v[1];
		this->Afile._user =v[2];
		this->Afile._hostA=v[3];
		this->Afile._portA=v[4];
		this->Afile._hostB=v[5];
		this->Afile._portB=v[6];
		this->Afile._date =v[7];
		this->Afile._url  =v[8];

//		this->Display();
		//cout<<endl;
	}
	fs.close();
}

LogSubB::LogSubB(thread_stu _ts)
	:ts(_ts)
{}

thread_stu LogSubB::GetTs()
{
	return ts;	
}

void LogSubB::SegField(string pathname)
{
	ifstream fs;
	fs.open(pathname.c_str());
	if(!fs)
	{
		cout<<"file open failed!"<<endl;
	}
	while(fs.peek()!=EOF)
	{
		string buf;
		char cbuf[1024];
		fs.getline(cbuf,1024);
		buf = cbuf;
	
		// 将已经分离的数据放在顺序表中
		vector<string> v;
		SaveField(v,buf);

		this->Bfile._phone=v[0];
		this->Bfile._num=v[1];
		this->Bfile._user=v[2];
		this->Bfile._host=v[3];
		this->Bfile._dateb=v[4];
		this->Bfile._datee=v[5];

//		this->Display();
		//cout<<endl;
	}
		
	fs.close();
}




char GetFileType(const string& filename)
{
	//1. 文件不存在
	if(filename.empty()||filename.length()==0)
	{
		cout<<"\033[35m  file is not exit\033[0m"<<endl;;
		return -1; //exit : 不能轻易使用，毕竟传过来的文件不知道会是什么类型，所以程序能不退出就绝不退出
	}	
	else //2.  获取文件名类型
	{
		if(filename.find(".ok")!=string::npos)
			return filename[0];
	}

}


int GetFilefd(string &filename)
{
	string pathname="./data/";		
	pathname+=filename;
	int fd = open(pathname.c_str(),O_RDONLY);

	return fd;
}

void LogSubA::Display()
{
	cout<<endl;
	cout<<"A Type File: "<<endl;
	cout<<"A-> phone: "<<this->Afile._phone<<endl;
	cout<<"A-> num  : "<<this->Afile._num  <<endl;
	cout<<"A-> user : "<<this->Afile._user <<endl;
	cout<<"A-> hostA: "<<this->Afile._hostA<<endl;
	cout<<"A-> portA: "<<this->Afile._portA<<endl;
	cout<<"A-> hostB: "<<this->Afile._hostB<<endl;
	cout<<"A-> portB: "<<this->Afile._portB<<endl;
	cout<<"A-> date : "<<this->Afile._date <<endl;
	cout<<"A-> url  : "<<this->Afile._url  <<endl;

		
}
void LogSubB::Display()
{

	cout<<endl;
	cout<<"B Type File: "<<endl;
	cout<<"B-> phone: "<<this->Bfile._phone<<endl;
	cout<<"B-> num: "<<Bfile._num<<endl;
	cout<<"B-> user: "<<this->Bfile._user<<endl;
	cout<<"B-> host: "<<this->Bfile._host<<endl;
	cout<<"B-> datebegin: "<<this->Bfile._dateb<<endl;
	cout<<"B-> dateend: "<<this->Bfile._datee<<endl;

}
