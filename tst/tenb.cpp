

#include "Primedat.h"
#include <string>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{

    string cmd;
	 Primedat *tenb;
	 if(argc == 1){
		 tenb=new Primedat(1000000000);
	 }else{
		 tenb = new Primedat(atoi(argv[1]));
	 }
	 if(tenb->initdat())
	 {
	  cout<<"�������ɵ����ݺܴ�һһ������ķѴ���ʱ��\n����\"show\"��ʾ��������������ַ��˳�:";
	  cin>>cmd;
	if(cmd == "show")
      {tenb->show();}
     }
	 delete tenb;
	 return 0;
}


