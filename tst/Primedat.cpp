
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
	arrsize = 4096; //win98һ���ڴ�ҳ4kb,�����ڴ���Ƭ
	arrnumlimit = arrsize * 40;
	int i = 0;
	for (i = 0; i < 16; i++) {
		andortable[i] = 1 << i;//�����ݱ���������ĳЩλ��ĳЩλ��1
	}
	int arrnum;
	arrnum = maxprime / arrnumlimit + (((maxprime % arrnumlimit) == 0) ? 0 : 1);
	cout << "arrnum: " << arrnum << endl;
	data = new unsigned short *[arrnum];//����һ��ָ������
	if (data == NULL) {
		cout << "���ָ���ģ���ڴ������󣬳��������ָ���Ĳ��������񱻷���" << endl;
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
	} catch (int datacunt) // �����ڴ�������
	{
		allocerr++;
		if (allocerr < 3) {
			cout << "�ڷ����" << datacunt + 1 << "���ڴ�ʱʧ�ܣ�ϵͳ���ڳ������·���" << endl;
			goto getmem;
		} else {
			cout << "�ڴ��������Ѵ�4�Σ����ܲ���ϵͳ�ڴ治�㡣" << endl << "���������ָ���Ĳ����������ȷ���"
					<< endl;
			exit(1);
		}
	}
	for (i = 0; i < pointercunt; i++)
		for (int k = 0; k < arrsize; k++) {
			*(*(data + i) + k) = 0; //��ʼ�����ݿ�
		}
	cout << "^_^ �ڴ��ʼ����ɣ�primedat��Ķ�����ɹ�" << endl;
}//Primedat();


//////////////////////////////////////////////////////////////////////////


Primedat::~Primedat() //�ͷ��ڴ�
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
	clock_t start; //���㿪ʼ����ֹʱ��
	int bs_goal = static_cast<int> (sqrt(this->goal));// the goal is the sqare of the large int
	short oflg = -1;
	short iflg = -1;
	start = clock(); //��ʼ��ʱ
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
		while (cnti <= igoal) //�ڲ��廷
		{

			(*(*(data + datID) + arrID)) |= andortable[bitblockID * 4
					+ ar[bitID]];
//			printf("mask:datID:%d,arrID:%d,bitblockID:%d, bitID:%d, on %d:%d\n"
//			, datID, arrID, bitblockID , bitID,  cnto,cnti
//			);

			//��һ�����������ڵ�λ��1
			iflg++;
			if (!iflg) //��־
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
			cout << basecunt << " ";//���һ������
			scrwd++;
			if (scrwd == 8) {
				scrwd = 0;
				cout << endl;//�ﵽ8��������
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


