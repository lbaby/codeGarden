//begin of Primedat.h  
#ifndef PRIMEDAT_CLASS_H
#define PRIMEDAT_CLASS_H

 class Primedat 
{ 
public:  
  Primedat(int maxprime); 
  ~Primedat(); 
  bool initdat(void);          //运算
  void show(void);              //打印这个数列 
private:
	//数组：
	int goal;
    int arrsize;             //win98 一个内存页4kB 
    unsigned short **data;       //指针数组，记录各数据数组的首地址 
    int arrnumlimit;          //一个数组所能标记的素数上限 
    int pointercunt;            //实际申请到的指针数组长度 释放内存标记 
    //

  ////一个数：
    int onedat;                //一个数
	int datID;          //内存块索引 
    int arrID;          //数组中数据索引 
    int bitblockID;          //数据内位块索引 
    int bitID;                  //位块内的位索引 
    
    /////
    
	int cnto;                 //外层计数器
	int cnti;                 //内层计数器
/////差别:
	int ddtID;
	int darID;
	int dblkID;
	int dbtID;

//差别4：
	int ddtID4;
	int darID4;
	int dblkID4;
	int dbtID4;
	
	
/////输出：
    int datacunt;             //实际申请到的数组个数释放内存标记 
    short scrwd;             //输出数据占屏幕宽度 
    unsigned short andortable[16];//标记各个数据位的数据表 
    short allocerr;           //内存分配错误次数 
} ; //原来的时候，这里少了个'；'所以出错 


#endif

//end of Primedat.h 

