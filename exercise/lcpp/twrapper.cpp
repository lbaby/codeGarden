#include <Wrapper.h>

#include <iostream>
#include <string>

int main(void)
{
	using namespace std;

	Int i(3);
	Char c('a');
	Double d(3.14);
	String s("String");

	int ii = i;
	int cc = c;
	double dd = d;
	string ss = s;

	cout <<"i: " << i <<" " <<ii << endl;
	cout <<"c: " << c <<" " <<cc <<endl;
	cout <<"d: " << d <<" " <<dd << endl;
	cout <<"s: " << s <<" " <<ss <<endl;
}

