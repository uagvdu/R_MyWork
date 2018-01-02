#include"LogAnalyze.h"



bool InitVp()
{
	DIR * dir = NULL;
	dir = opendir("./data");
	struct dirent* ptr=NULL;

	int i = 0;
	while(i!=ARR_SIZE&&(ptr=readdir(dir)))
	{
		string filename(ptr->d_name);	
		if(filename.find(".ok") == string::npos)
		{
			continue;
		}
		string pathname=string("./data/")+filename;
		vp[i]=pair<string,bool>(pathname,true);	
		i++;	
	}
	status  = i;
	closedir(dir);
	if(vp[0].second == true )
	{
		return true;

	}
	else
	{
		//cout<<"Init: "<<false<<endl;
		return false;
	}
}


//条件变量的设置是指： 当十个线程一次性将文件都处理好之后，才向vp里面重新添加文件 : 控制好一次性处理文件的线程数量
bool run1(void *args)
{
	DIR * dir = NULL;
	dir = opendir("./data");
	struct dirent* ptr=NULL;

	int i = 0;
	/**********************************/
	if(status != 0)	
	{
		closedir(dir);
		return false ;
	}
	//	pthread_cond_wait(&cond,&mutex);
	/*******************************/

	cout<<"enter run"<<status<<endl;
	pthread_mutex_lock(&mutex);

	pthread_mutex_lock(&cmutex);
	
	while(i!=ARR_SIZE&&(ptr=readdir(dir)))
	{
		string filename(ptr->d_name);	
		if(filename.find(".ok") == string::npos)
		{
			continue;
		}
		string pathname=string("./data/")+filename;
		vp[i]=pair<string,bool>(pathname,true);	
		
		i++;	
	}
	status = i;
	pthread_mutex_unlock(&cmutex);
	pthread_mutex_unlock(&mutex);
	closedir(dir);
	return true;
	
}



void GetFileName(string &pathname)
{
	/******* 获取文件名 **********/
	int i = 0;
	pthread_mutex_lock(&mutex); //这个锁的加在这里，决定了每一次只有一个线程去获取
	while(i<ARR_SIZE)
	{
		if(vp[i].second==true)
		{
			pathname = vp[i].first;		
			vp[i].second = false;
			break;
		}
		i++;
	}
	pthread_mutex_unlock(&mutex);
	if(pathname.length()==0)
		pthread_exit(NULL);
	/*************************************/
}
void* thread_run2(void* args)
{
		
	string pathname;
	GetFileName(pathname);
//	cout<<"pathname: "<<pathname<<endl;	

	char c =CheckFileType(pathname);
	switch(c)
	{
		case 'A':
			{
				LogSubA log;
				log.SegField(pathname);
				break;
			}
		case 'B':
			{
				LogSubB log;
				log.SegField(pathname);
				break;
			}
	
		default:
			break;
	}

	
}


char CheckFileType(const string& pathname)
{
	//1. 文件不存在
	if(pathname.empty()||pathname.length()==0)
	{
		cout<<"\033[35m  file is not exit\033[0m"<<endl;;
		return -1; //exit : 不能轻易使用，毕竟传过来的文件不知道会是什么类型，所以程序能不退出就绝不退出
	}	

	if(pathname.find('A') != string::npos)
		return  'A';
	else if(pathname.find('B')!=string::npos) 
	{
		return 'B';
	}

}
	

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
		
		
		this->InsertSQL();
	}
	remove(pathname.c_str());
	pthread_mutex_lock(&cmutex);
	status--;
	pthread_mutex_unlock(&cmutex);
	cout<<"sql_count: "<<sql_count<<endl;
	pthread_exit(NULL);

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


		this->InsertSQL();
		//cout<<endl;
	}
		
	fs.close();
	remove(pathname.c_str());

	pthread_mutex_lock(&cmutex);
	status--;
	pthread_mutex_unlock(&cmutex);
	cout<<"sql_count: "<<sql_count<<endl;
	pthread_exit(NULL);
	
}

void LogSubA::InsertSQL()
{

	
	string phone = this->Afile._phone;
	string num   = this->Afile._num  ;
	string user  = this->Afile._user ;
	string hostA = this->Afile._hostA;
	string portA = this->Afile._portA;
	string hostB = this->Afile._hostB;
	string portB = this->Afile._portB;
	string date  = this->Afile._date ;
	string url   = this->Afile._url  ;
	
	char buf[1024];
	memset(buf,'0',1024);	
	sprintf(buf,"INSERT INTO logA(user,phone,num,hostA,portA,hostB,portB,date,url)VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s');",user.c_str(),phone.c_str(),num.c_str(),hostA.c_str(),portA.c_str(),hostB.c_str(),portB.c_str(),date.c_str(),url.c_str());
	  
	if(mysql_query(conn,buf)!=0) // 成功返回值为0
	{
		cout<<"mysql_query failed !"<<endl;
		exit(3);
		
	}
	pthread_mutex_lock(&sql_mutex);
	sql_count++;
	pthread_mutex_unlock(&sql_mutex);


		
}
void LogSubB::InsertSQL()
{

	string phone = this->Bfile._phone;
	string num   = this->Bfile._num  ;
	string user  = this->Bfile._user ;
	string host = this->Bfile._host;
	string dateb  = this->Bfile._dateb ;
	string datee   = this->Bfile._datee  ;
	

	char buf[1024];
	memset(buf,'0',1024);	
	sprintf(buf,"INSERT INTO logB(user,phone,num,host,dateb,datee)VALUES('%s','%s','%s','%s','%s','%s');",user.c_str(),phone.c_str(),num.c_str(),host.c_str(),dateb.c_str(),datee.c_str());
	  
	if(mysql_query(conn,buf)!=0) // 成功返回值为0
	{
		cout<<"mysql_query failed !"<<endl;
		exit(3);
		
	}
	pthread_mutex_lock(&sql_mutex);
	sql_count++;
	pthread_mutex_unlock(&sql_mutex);

}


LogSubA::LogSubA()
{
	conn=mysql_init(NULL);	
	if(!conn)
	{
		cout<<"Init failed!"<<endl;
		exit(1);
	}
	
	if(mysql_real_connect(conn,"localhost","adobe","2582","Concurrency",0,NULL,0)==NULL)
	{
		cout<<"connect failed!"<<endl;
		exit(2);
		
	}
}
LogSubB::LogSubB()
{
	conn=mysql_init(NULL);	
	if(!conn)
	{
		cout<<"Init failed!"<<endl;
		exit(1);
	}
	
	if(mysql_real_connect(conn,"localhost","adobe","2582","Concurrency",0,NULL,0)==NULL)
	{
		cout<<"connect failed!"<<endl;
		exit(2);
		
	}
}
