#include <iostream>
using namespace std;
int main(void)
{
struct CLS
{
int m_i;
CLS( int i ) : m_i(i) {cout <<"aaa"<<this<<endl;}
CLS()
{
cout <<"aaa"<<this<<endl;
CLS(1000);
}
};
CLS obj;
cout << obj.m_i << endl; 
}
