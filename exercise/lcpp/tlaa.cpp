#include <ListAsArray.h>
#include <Wrapper.h>
#include <PuttingVisitor.h>


#include <iostream>

int main(void)
{
	using namespace std;
	
	ListAsArray laa(100);
	PuttingVisitor pv(cout);
	
	
	
	
	laa.Insert(* new Int(3) );
	laa.Insert(* new Int(4) );
	laa.Insert(* new Int(6) );
	
	laa.Accept(pv);
	cout <<endl << endl;
	
	Int i4(4);
	Int i3(3);
	Int i6(6);
	
	Int *ip5 = new Int(5);
	laa.InsertAfter(laa.FindPosition(i4), *ip5 );
	laa.Accept(pv);
	cout <<endl << endl;
	
	laa.InsertBefore(laa.FindPosition(i3), *new Int(2) );
	laa.Accept(pv);
	cout <<endl << endl;
	

	for (int i = 0 ; i < 5 ; i ++){
		cout << "[unsigned  ]" <<  laa[i]<<endl;
		Int ii (i + 2);
		cout << "[position  ]" <<   laa[laa.FindPosition(ii) ]  << endl;
		
	}
	
	cout << "Int i3(3) is member? == " << laa.IsMember(i3) << endl;
	
		cout << " ip5 find? "<<  laa.Find(*ip5) << endl;
	cout << "Int *ip5  is member? == " << laa.IsMember(*ip5) << endl;
	
	laa.Withdraw(*ip5);
	delete ip5;
	cout << "after draw ip5 ";
	laa.Accept(pv);
	cout <<endl << endl;
	


}
