#include"test.h"

char LogAnalyze::JudgeFileType(const string& pathname)
{
	//1. 文件不存在
	if(pathname.empty()||pathname.length()==0)
	{
		cout<<"\033[35m  file is not exit\033[0m"<<endl;;
		exit(1);

	}	
	else //2.  获取文件名
	{
		char buf[pathname.length()+1] ;

		strcpy(buf,pathname.c_str());
	    char* filename=basename(buf);		
		if(*filename == 'A')
		{
			cout<<"A File: " <<filename<<endl;
			return 'A';
		}
		else if(*filename == 'B')
		{
			cout<<"B File: "<<filename<<endl;
			return 'B';
		}
		else
		{
			cout<<"Not A&B File"<<endl;
			exit(2);
		}

	}

}

int  LogAnalyze::ReadLine(string &buf,int fd,int NUM)
{
	char c=0 ;
	//memset(buf.c_str(),'0',1024);
	
	while(1)
	{
		ssize_t sz = read(fd,&c,1);
		if(sz<=0)
		{	
			return -1;
		}
		if(c=='\n')
			break;
		buf.push_back(c);
	}

	buf.push_back('\0');
	return 1;
}

void LogAnalyze::SaveField(vector<string>& v,string &buf)
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
	tmp = buf.substr(index1+1,buf.length()-1-index1-1);
	v.push_back(tmp);
}

void LogAnalyze::SegField(int fd,char ft,int NUM)			
{
	// 只读了一行，目标是完成一个文件的读取
	int i=1;
	do
	{
		string buf;
		i = ReadLine(buf,fd,NUM);
		if(i<0)
		{
			break;
		}
		cout<<"ReadLine: "<<buf<<endl;
	
		int index = buf.find("|");
	
		// 将已经分离的数据放在顺序表中
		vector<string> v;
		SaveField(v,buf);
	
		// vector 已经放好数据，下面的条件视为了让数据准确的放在合适的位置中
		
	 	if(ft == 'A')
		{
			this->Afile._phone=v[0];
			this->Afile._num  =v[1];
			this->Afile._user =v[2];
			this->Afile._hostA=v[3];
			this->Afile._portA=v[4];
			this->Afile._hostB=v[5];
			this->Afile._portB=v[6];
			this->Afile._date =v[7];
			this->Afile._url  =v[8];
		}
		else 
		{
			this->Bfile._phone=v[0];
			this->Bfile._num=v[1];
			this->Bfile._user=v[2];
			this->Bfile._host=v[3];
			this->Bfile._dateb=v[4];
			this->Bfile._datee=v[5];
			
		}
		this->Display(ft);
		cout<<endl;
	}while(i>0); 
}

string LogAnalyze::GetNumLogCon(int fd,char ft,int NUM)
{

	if(ft=='A'||ft == 'B')
	{
		SegField(fd,ft,NUM);
		return string();
	}
	else
	{
		cout<<"File Type isn't exit!"<<endl;
		exit(3);
	}
}

void LogAnalyze::Display(char ft)
{
	if(ft=='A') 
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
	else
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
}
