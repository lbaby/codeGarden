#include <ListAsLinkedList.h>
#include <Wrapper.h>
#include <PuttingVisitor.h>


#include <iostream>

int main(void)
{
	using namespace std;
	
	ListAsLinkedList lll;
	PuttingVisitor pv(cout);
	
	
	
	
	lll.Insert(* new Int(3) );
	lll.Insert(* new Int(4) );
	lll.Insert(* new Int(6) );
	
	lll.Accept(pv);
	cout <<endl << endl;
	
	Int i4(4);
	Int i3(3);
	Int i6(6);
	
	Int *ip5 = new Int(5);
	lll.InsertAfter(lll.FindPosition(i4), *ip5 );
	lll.Accept(pv);
	cout <<endl << endl;
	
	lll.InsertBefore(lll.FindPosition(i3), *new Int(2) );
	lll.Accept(pv);
	cout <<endl << endl;
	

	for (int i = 0 ; i < 5 ; i ++){
		cout << "[unsigned  ]" <<  lll[i]<<endl;
		Int ii (i + 2);
		cout << "[position  ]" <<   lll[lll.FindPosition(ii) ]  << endl;
		
	}
	
	cout << "Int i3(3) is member? == " << lll.IsMember(i3) << endl;
	
		cout << " ip5 find? "<<  lll.Find(*ip5) << endl;
	cout << "Int *ip5  is member? == " << lll.IsMember(*ip5) << endl;
	
	lll.Withdraw(*ip5);
	delete ip5;
	cout << "after draw ip5 ";
	lll.Accept(pv);
	cout <<endl << endl;
	


}
