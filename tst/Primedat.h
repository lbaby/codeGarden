//begin of Primedat.h  
#ifndef PRIMEDAT_CLASS_H
#define PRIMEDAT_CLASS_H

 class Primedat 
{ 
public:  
  Primedat(int maxprime); 
  ~Primedat(); 
  bool initdat(void);          //����
  void show(void);              //��ӡ������� 
private:
	//���飺
	int goal;
    int arrsize;             //win98 һ���ڴ�ҳ4kB 
    unsigned short **data;       //ָ�����飬��¼������������׵�ַ 
    int arrnumlimit;          //һ���������ܱ�ǵ��������� 
    int pointercunt;            //ʵ�����뵽��ָ�����鳤�� �ͷ��ڴ��� 
    //

  ////һ������
    int onedat;                //һ����
	int datID;          //�ڴ������ 
    int arrID;          //�������������� 
    int bitblockID;          //������λ������ 
    int bitID;                  //λ���ڵ�λ���� 
    
    /////
    
	int cnto;                 //��������
	int cnti;                 //�ڲ������
/////���:
	int ddtID;
	int darID;
	int dblkID;
	int dbtID;

//���4��
	int ddtID4;
	int darID4;
	int dblkID4;
	int dbtID4;
	
	
/////�����
    int datacunt;             //ʵ�����뵽����������ͷ��ڴ��� 
    short scrwd;             //�������ռ��Ļ��� 
    unsigned short andortable[16];//��Ǹ�������λ�����ݱ� 
    short allocerr;           //�ڴ���������� 
} ; //ԭ����ʱ���������˸�'��'���Գ��� 


#endif

//end of Primedat.h 

