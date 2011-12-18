
//Begin of Primedat.cpp


#include"Primedat.h"
#include<string>
#include<iostream>
#include<ctime>
#include<cmath>
using namespace std;
Primedat::Primedat(int maxprime) {
	goal = maxprime;
	allocerr = 0;
	arrsize = 4096; //win98一个内存页4kb,减少内存碎片
	arrnumlimit = arrsize * 40;
	int i = 0;
	for (i = 0; i < 16; i++) {
		andortable[i] = 1 << i;//此数据表用来屏蔽某些位或将某些位置1
	}
	int arrnum;
	arrnum = maxprime / arrnumlimit + (((maxprime % arrnumlimit) == 0) ? 0 : 1);
	cout << "arrnum: " << arrnum << endl;
	data = new unsigned short *[arrnum];//建立一个指针数组
	if (data == NULL) {
		cout << "存放指针的模块内存分配错误，程序不能完成指定的操作，任务被放弃" << endl;
		exit(1);
	}
	pointercunt = arrnum;
	datacunt = 0;
	getmem: try {
		for (; datacunt < arrnum; datacunt++) {
			*(data + datacunt) = new unsigned short[arrsize];
			if ((*(data + datacunt)) == NULL) {
				throw datacunt;
			}
		}
	} catch (int datacunt) // 处理内存分配错误
	{
		allocerr++;
		if (allocerr < 3) {
			cout << "在分配第" << datacunt + 1 << "块内存时失败，系统正在尝试重新分配" << endl;
			goto getmem;
		} else {
			cout << "内存分配错误已达4次，可能操作系统内存不足。" << endl << "程序不能完成指定的操作，任务被迫放弃"
					<< endl;
			exit(1);
		}
	}
	for (i = 0; i < pointercunt; i++)
		for (int k = 0; k < arrsize; k++) {
			*(*(data + i) + k) = 0; //初始化数据块
		}
	cout << "^_^ 内存初始化完成，primedat类的对象构造成功" << endl;
}//Primedat();


//////////////////////////////////////////////////////////////////////////


Primedat::~Primedat() //释放内存
{
	for (int i = 0; i < pointercunt; i++) {
		delete[] (*(data + i));
	}
	delete[] data;
}//end of ~Primedat()


//////////////////////////////////////////////////////////////////////////

bool Primedat::initdat(void) {

	int ar[10];
	ar[1] = 0;
	ar[3] = 1;
	ar[7] = 2;
	ar[9] = 3;
	clock_t start; //计算开始和终止时间
	int bs_goal = static_cast<int> (sqrt(this->goal));// the goal is the sqare of the large int
	short oflg = -1;
	short iflg = -1;
	start = clock(); //开始计时
	cnto = 3;
	bool overflow = 0;

	while (cnto <= bs_goal) {
		cnti = cnto;
		datID = (cnto * cnto) / arrnumlimit;
		arrID = ((cnto * cnto) % arrnumlimit) / 40;
		bitblockID = ((cnto * cnto) % 40) / 10;
		bitID = (cnto * cnto) % 10;
		//by 2:

		ddtID = (cnto * 2) / arrnumlimit;
		darID = ((cnto * 2) % arrnumlimit) / 40;
		dblkID = ((cnto * 2) % 40) / 10;
		dbtID = (cnto * 2) % 10;
		//by 4:
		ddtID4 = (cnto * 4) / arrnumlimit;
		darID4 = ((cnto * 4) % arrnumlimit) / 40;
		dblkID4 = ((cnto * 4) % 40) / 10;
		dbtID4 = (cnto * 4) % 10;
		iflg = oflg;
		int igoal = this->goal / cnto;
//		printf("%d:ig\n",igoal);
		while (cnti <= igoal) //内层徨环
		{

			(*(*(data + datID) + arrID)) |= andortable[bitblockID * 4
					+ ar[bitID]];
//			printf("mask:datID:%d,arrID:%d,bitblockID:%d, bitID:%d, on %d:%d\n"
//			, datID, arrID, bitblockID , bitID,  cnto,cnti
//			);

			//将一个非素数所在的位置1
			iflg++;
			if (!iflg) //标志
			{
				iflg = -4;
				cnti += 4;
				bitID += dbtID4;
				if (bitID >= 10) {
					bitID -= 10;
					bitblockID++;
					if (bitblockID >= 4) {
						bitblockID -= 4;
						arrID++;
						if (arrID >= arrsize) {
							arrID -= arrsize;
							datID ++;
						}
					}

				}//bitID


				bitblockID += dblkID4;
				if (bitblockID >= 4) {
					bitblockID -= 4;
					arrID++;
					if (arrID >= arrsize) {
						arrID -= arrsize;
						datID ++;
					}
				}

				arrID += darID4 ;
				if (arrID >= arrsize) {
					arrID -= arrsize;
					datID ++;
				}

				datID += ddtID4;

			} //if

			else {
				cnti += 2;
								bitID += dbtID;
								if (bitID >= 10) {
									bitID -= 10;
									bitblockID++;
									if (bitblockID >= 4) {
										bitblockID -= 4;
										arrID++;
										if (arrID >= arrsize) {
											arrID -= arrsize;
											datID ++;
										}
									}

								}//bitID


								bitblockID += dblkID;
								if (bitblockID >= 4) {
									bitblockID -= 4;
									arrID++;
									if (arrID >= arrsize) {
										arrID -= arrsize;
										datID ++;
									}
								}

								arrID += darID ;
								if (arrID >= arrsize) {
									arrID -= arrsize;
									datID ++;
								}

								datID += ddtID;


			}//else

		} //while

		oflg++;
		if (!oflg) {
			oflg = -4;
			cnto += 4;
		} else {
			cnto += 2;
		}

		//

	}// while  out
	clock_t end = clock();
	cout << "time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
	return true;
} //initdat(void)


//////////////////////////////////////////////////////////////////////


void Primedat::show(void) {
	int ar[10];
	ar[1] = 0;
	ar[3] = 1;
	ar[7] = 2;
	ar[9] = 3;

	unsigned short tmp;
	int basecunt;
	int baseflag;
	baseflag = 3;
	for (basecunt = 3; basecunt < this->goal;) {

		datID = basecunt / arrnumlimit;
		arrID = (basecunt % arrnumlimit) / 40;
		bitblockID = (basecunt % 40) / 10;
		bitID = ar[(basecunt % 10)];

		tmp = *(*(data + datID) + arrID);

		if (!(tmp & andortable[bitblockID * 4 + bitID])) {
			cout << basecunt << " ";//输出一个素数
			scrwd++;
			if (scrwd == 8) {
				scrwd = 0;
				cout << endl;//达到8个数后换行
			}
		}

		baseflag++;
		if (baseflag == 4) {
			basecunt += 4;
			baseflag = 0;
		} else {
			basecunt += 2;
		}
	}
	cout << "end" << endl;
}//end of function

//////////////////////////////////////////////////////////////////////////


