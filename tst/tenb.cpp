

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
	  cout<<"由于生成的数据很大，一一输出将耗费大量时间\n输入\"show\"显示结果，其它任意字符退出:";
	  cin>>cmd;
	if(cmd == "show")
      {tenb->show();}
     }
	 delete tenb;
	 return 0;
}


